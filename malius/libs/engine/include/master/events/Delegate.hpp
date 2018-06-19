#pragma once

//#include <utility>
#include <functional>
#include <cassert>
#include <memory>

#include <malius/core/lang.hpp>

namespace ma
{
    template <typename Signature>
    class Delegate;

    template <typename R, typename ...Args>
    class Delegate<R(Args ...)>
    {
        // function ptr
        typedef R(*ProxyFunctionPtr)(void *, Args &&...);

#pragma region proxies
        /// turns a free function into our internal function proxy
        template <R(*FunctionPtr)(Args...)>
        static  MA_INLINE R FunctionProxy(void *, Args &&...args)
        {
            // we don't need the instance pointer because we're dealing with free functions
            return (FunctionPtr)(::std::forward<Args>(args)...);
        }

        /// turns a member function into our internal function proxy
        template <class C, R(C::*MethodPtr)(Args...)>
        static  MA_INLINE R MethodProxy(void *instance, Args &&...args)
        {
            return (static_cast<C *>(instance)->*MethodPtr)(::std::forward<Args>(args)...);
        }

        /// turns a const member function into our internal function proxy
        template <class C, R(C::*MethodPtr)(Args...) const>
        static  MA_INLINE R ConstMethodProxy(void *instance, Args &&...args)
        {
            return (static_cast<C const *>(instance)->*MethodPtr)(::std::forward<Args>(args)...);
        }
#pragma endregion

    public:
        // constructor
        Delegate(void)
            : instance_(nullptr)
            , proxyFuncPtr_(nullptr)
        {
        }

        // deconstructor
        ~Delegate(void)
        {
            Unbind();
        }

        // copy constructor
        Delegate(Delegate const &) = default;

        // move constructor
        Delegate(Delegate &&) = default;

        // copy assignment operator
        Delegate& operator=(Delegate const &) = default;

        // move assignment operator
        Delegate& operator=(Delegate &&) = default;

        //// copy assignment operator
        //Delegate& operator=(Delegate const & other)
        //{
        //    instance_ = other.instance_;
        //    proxyFuncPtr_ = other.proxyFuncPtr_;
        //    return *this;
        //}

        //// move assignment operator
        //Delegate& operator=(Delegate&& other)
        //{
        //    instance_ = other.instance_;
        //    proxyFuncPtr_ = other.proxyFuncPtr_;
        //    other.instance_ = nullptr;
        //    other.proxyFuncPtr_ = nullptr;
        //    return *this;
        //}

        //// alternatively, replace both assignment operators with 
        ////  Delegate& operator=(Delegate other)
        ////  {
        ////      std::swap(instance_, other.instance_);
        ////      std::swap(proxyFuncPtr_, other.proxyFuncPtr_);
        ////      return *this;
        ////  }

#pragma region Bind

        /// Binds a free/static function
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE void Bind(void)
        {
            instance_ = nullptr;
            proxyFuncPtr_ = &FunctionProxy<FunctionPtr>;
        }

#if defined(_MSC_VER) && (_MSC_VER < 1800)
        /// The reason you cannot call both methods Bind is due to overload resolution.
        /// Each instance can implicitly be converted into a const C*, 
        /// so the compiler will never try to use the first overload. 
        /// We need to force the compiler into only using the non-const overload 
        /// if the template argument is a non-const member function, and vice versa.
        /// By introducing two helpers called NonConstWrapper and ConstWrapper, we achieve two things:
        /// 1) Both Bind methods are now truly different overloads, taking different arguments.
        /// 2) By using non-explicit constructors in our helpers, the arguments need to always undergo implicit conversion.
        /// Because the template argument Function is part of the function argument (so to say), 
        /// only non-const member functions can be converted into a NonConstWrapper temporary, 
        /// and const member functions need to take the ConstWrapper overload.
        template <class C, R(C::*FunctionPtr)(Args...)>
        struct NonConstWrapper
        {
            NonConstWrapper(C *instance)
                : instance_(instance)
            {
            }

            C *instance_;
        };

        template <class C, R(C::*FunctionPtr)(Args...) const>
        struct ConstWrapper
        {
            ConstWrapper(C const *instance)
                : instance_(instance)
            {
            }

            C const *instance_;
        };

        /// Binds a class method
        template <class C, R(C::*FunctionPtr)(Args...)>
        void Bind(NonConstWrapper<C, FunctionPtr> wrapper)
        {
            m_stub.first.as_void = wrapper.instance_;
            m_stub.second = &MethodProxy<C, FunctionPtr>;
        }

        /// Binds a const class method
        template <class C, R(C::*FunctionPtr)(Args...) const>
        void Bind(ConstWrapper<C, FunctionPtr> wrapper)
        {
            m_stub.first.as_void_const = wrapper.instance_;
            m_stub.second = &ConstMethodProxy<C, FunctionPtr>;
        }
#else
        /// Binds a member function
        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE void Bind(C *instance)
        {
            instance_ = instance;
            proxyFuncPtr_ = &MethodProxy<C, MethodPtr>;
        }

        /// Binds a const member function
        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE void Bind(C const *instance)
        {
            instance_ = const_cast<C *>(instance);
            proxyFuncPtr_ = &ConstMethodProxy<C, MethodPtr>;
        }
#endif

#pragma endregion

         MA_INLINE void Unbind(void)
        {
            instance_ = nullptr;
            proxyFuncPtr_ = nullptr;
        }

#pragma region Make

        // In order to make use of the RAII pattern
        // A static factory method can be used to create delegates.

        /// Make Delegate from free/static function
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE static Delegate Make(void)
        {
            Delegate<R(Args...)> delegate;
            delegate.Bind<FunctionPtr>();
            return ::std::move(delegate);
        }

        /// Make Delegate from member function
        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE static Delegate Make(C *instance)
        {
            Delegate<R(Args...)> delegate;
            delegate.Bind<C, MethodPtr>(instance);
            return ::std::move(delegate);
        }

        /// Make Delegate from const member function
        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE static Delegate Make(C const *instance)
        {
            Delegate<R(Args...)> delegate;
            delegate.Bind<C, MethodPtr>(instance);
            return ::std::move(delegate);
        }

#pragma endregion

        /// Invokes the delegate
         MA_INLINE R Invoke(Args &&...args) const
        {
            // TODO: Verify that the user object is still valid.
            // MA_ASSERT(m_stub.second != nullptr, "Cannot invoke unbound delegate. Call Bind() first.")();
            assert((proxyFuncPtr_ != nullptr) && "Cannot Invoke unbound Delegate. Call Bind first.");

            return proxyFuncPtr_(instance_, ::std::forward<Args>(args)...);
        }

        // MA_INLINE R operator()(Args &&...args) const
        //{
        //    return Invoke(::std::forward<Args>(args)...);
        //}

         MA_INLINE bool operator==(Delegate const &other) const noexcept
        {
            return (proxyFuncPtr_ == other.proxyFuncPtr_) 
                && (instance_ == other.instance_);
        }

         MA_INLINE bool operator!=(Delegate const &other) const noexcept
        {
            return !operator==(other);
        }

         MA_INLINE bool operator==(::std::nullptr_t) const noexcept
        {
            return proxyFuncPtr_ == nullptr;
        }

         MA_INLINE bool operator!=(::std::nullptr_t) const noexcept
        {
            return proxyFuncPtr_ != nullptr;
        }

        // either explicit (C++11) or use Safe Bool Idiom
        // http://www.artima.com/cppsource/safebool.html
         MA_INLINE explicit operator bool() const noexcept { return proxyFuncPtr_ != nullptr; }

         MA_INLINE bool IsBound(void) const noexcept { return proxyFuncPtr_ != nullptr; }

    private:
        //enum Type : char
        //{
        //    weak_ptr = 1 << 0,  // 0b0001
        //    raw_ptr  = 1 << 1   // 0b0010
        //};

        void *instance_;
        ProxyFunctionPtr proxyFuncPtr_;
    };
}
