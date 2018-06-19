#pragma once

// standard libraries
//#include <utility>
#include <functional>
#include <cassert>
#include <memory>

#include <malius/core/lang.hpp>

namespace ma
{
    template <typename Signature>
    class SmartDelegate;

    template <typename R, typename ...Args>
    class SmartDelegate<R(Args ...)>
    {
        // function ptr
        typedef R(*ProxyFunctionPtr)(std::weak_ptr<void> const &, Args &&...);

#pragma region proxies
        /// turns a free function into our internal function proxy
        template <R(*FunctionPtr)(Args...)>
        static  MA_INLINE R FunctionProxy(std::weak_ptr<void> const &, Args &&...args)
        {
            // we don't need the instance pointer because we're dealing with free functions
            return (FunctionPtr)(::std::forward<Args>(args)...);
        }

        /// turns a member function into our internal function proxy
        template <class C, R(C::*MethodPtr)(Args...)>
        static  MA_INLINE R MethodProxy(std::weak_ptr<void> const & instance, Args &&...args)
        {
            assert(!instance.expired() && "The instance has expired!");
            auto instancePtr = instance.lock();
            return (static_cast<C *>(instancePtr.get())->*MethodPtr)(::std::forward<Args>(args)...);
        }

        /// turns a const member function into our internal function proxy
        template <class C, R(C::*MethodPtr)(Args...) const>
        static  MA_INLINE R ConstMethodProxy(std::weak_ptr<void> const & instance, Args &&...args)
        {
            assert(!instance.expired() && "The instance has expired!");
            auto instancePtr = instance.lock();
            return (static_cast<C const *>(instancePtr.get())->*MethodPtr)(::std::forward<Args>(args)...);
        }
#pragma endregion

    public:
        // constructor
        SmartDelegate(void)
            //: instance_(nullptr)
            : weakInstance_()
            , proxyFuncPtr_(nullptr)
        {
        }

        // deconstructor
        ~SmartDelegate(void)
        {
            Unbind();
        }

        // copy constructor
        SmartDelegate(SmartDelegate const &) = default;

        // move constructor
        SmartDelegate(SmartDelegate &&) = default;

        // copy assignment operator
        SmartDelegate& operator=(SmartDelegate const &) = default;

        // move assignment operator
        SmartDelegate& operator=(SmartDelegate &&) = default;

        //// copy assignment operator
        //SmartDelegate& operator=(SmartDelegate const & other)
        //{
        //    instance_ = other.instance_;
        //    proxyFuncPtr_ = other.proxyFuncPtr_;
        //    return *this;
        //}

        //// move assignment operator
        //SmartDelegate& operator=(SmartDelegate&& other)
        //{
        //    instance_ = other.instance_;
        //    proxyFuncPtr_ = other.proxyFuncPtr_;
        //    other.instance_ = nullptr;
        //    other.proxyFuncPtr_ = nullptr;
        //    return *this;
        //}

        //// alternatively, replace both assignment operators with 
        ////  SmartDelegate& operator=(SmartDelegate other)
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
            weakInstance_.reset();
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
         MA_INLINE void Bind(std::shared_ptr<C> const & instance)
        {
            //auto test = std::static_pointer_cast<void>(instance);
            //std::weak_ptr<void> test_ptr = test;
            weakInstance_ = instance;
            proxyFuncPtr_ = &MethodProxy<C, MethodPtr>;
        }

        /// Binds a const member function
        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE void Bind(std::shared_ptr<C const> const & instance)
        {
            weakInstance_ = std::const_pointer_cast<C>(instance);
            proxyFuncPtr_ = &ConstMethodProxy<C, MethodPtr>;
        }
#endif

#pragma endregion

         MA_INLINE void Unbind(void)
        {
            weakInstance_.reset();
            proxyFuncPtr_ = nullptr;
        }

#pragma region Make

        // In order to make use of the RAII pattern
        // A static factory method can be used to create delegates.

        /// Make SmartDelegate from free/static function
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE static SmartDelegate Make(void)
        {
            SmartDelegate<R(Args...)> delegate;
            delegate.Bind<FunctionPtr>();
            return ::std::move(delegate);
        }

        /// Make SmartDelegate from member function
        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE static SmartDelegate Make(std::shared_ptr<C>& instance)
        {
            SmartDelegate<R(Args...)> delegate;
            delegate.Bind<C, MethodPtr>(instance);
            return ::std::move(delegate);
        }

        /// Make SmartDelegate from const member function
        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE static SmartDelegate Make(std::shared_ptr<C const>& instance)
        {
            SmartDelegate<R(Args...)> delegate;
            delegate.Bind<C, MethodPtr>(instance);
            return ::std::move(delegate);
        }

#pragma endregion

        /// Invokes the delegate
         MA_INLINE R Invoke(Args &&...args) const
        {
            // Verify that the user object is still valid.
            // MA_ASSERT(m_stub.second != nullptr, "Cannot invoke unbound delegate. Call Bind() first.")();
            assert((proxyFuncPtr_ != nullptr) && "Cannot Invoke unbound SmartDelegate. Call Bind first.");
            //assert(!weakInstance_.expired() && "The instance has expired!");

            //if (auto instancePtr = weakInstance_.lock())
            //{
            //    return proxyFuncPtr_(instancePtr.get(), ::std::forward<Args>(args)...);
            //}
            //else
            //{
            //    // expired
            //}

            return proxyFuncPtr_(weakInstance_, ::std::forward<Args>(args)...);
        }

        // MA_INLINE R operator()(Args &&...args) const
        //{
        //    return Invoke(::std::forward<Args>(args)...);
        //}

         MA_INLINE bool operator==(SmartDelegate const &other) const noexcept
        {
            return (proxyFuncPtr_ == other.proxyFuncPtr_) 
                && (weakInstance_ == other.weakInstance_);
        }

         MA_INLINE bool operator!=(SmartDelegate const &other) const noexcept
        {
            return !operator==(other);
        }

         MA_INLINE bool operator==(::std::nullptr_t const) const noexcept
        {
            return proxyFuncPtr_ == nullptr;
        }

         MA_INLINE bool operator!=(::std::nullptr_t const) const noexcept
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

        //Type type_;
        //union
        //{
        std::weak_ptr<void> weakInstance_;
        //void *instance_;
        //};
        ProxyFunctionPtr proxyFuncPtr_;
    };
}
