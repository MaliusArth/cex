#pragma once

#include <utility>
#include <algorithm>
#include <functional>
#include <list>
#include <cassert>
//#include <initializer_list>

#include <malius/core/lang.hpp>

namespace ma
{
    template <typename Signature>
    class MulticastDelegate;

    template <typename R, typename ...Args>
    class MulticastDelegate<R(Args...)>
    {
        // function ptr
        typedef R(*ProxyFunctionPtr)(void *, Args &&...);
        typedef std::pair<void *, ProxyFunctionPtr> proxy_pair_t;
        typedef std::list<proxy_pair_t> invocation_list_t;

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

        template <class C, R(C::*MethodPtr)(Args...) const>
        static  MA_INLINE R ConstMethodProxy(void *instance, Args &&...args)
        {
            return (static_cast<C const *>(instance)->*MethodPtr)(::std::forward<Args>(args)...);
        }
#pragma endregion

    public:
        // constructor
        MulticastDelegate(void) = default;

        // deconstructor
        ~MulticastDelegate(void)
        {
            UnbindAll();
        }

        // copy constructor
        MulticastDelegate(MulticastDelegate const &) = default;

        // move constructor
        MulticastDelegate(MulticastDelegate &&) = default;

        // copy assignment operator
        MulticastDelegate& operator=(MulticastDelegate const &) = default;

        // move assignment operator
        MulticastDelegate& operator=(MulticastDelegate &&) = default;

#pragma region Bind

        /// Binds a free function
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE void Bind(void)
        {
            //invocationList_.push_back(std::make_pair(nullptr, &FunctionProxy<FunctionPtr>));
            invocationList_.emplace_back(std::make_pair(nullptr, &FunctionProxy<FunctionPtr>));
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
            NonConstWrapper(C* instance)
                : instance_(instance)
            {
            }

            C* instance_;
        };

        template <class C, R(C::*FunctionPtr)(Args...) const>
        struct ConstWrapper
        {
            ConstWrapper(const C* instance)
                : instance_(instance)
            {
            }

            const C* instance_;
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
        /// Binds a class method
        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE void Bind(C *instance)
        {
            //invocationList_.push_back(std::make_pair(instance, &MethodProxy<C, MethodPtr>));
            invocationList_.emplace_back(std::make_pair(instance, &MethodProxy<C, MethodPtr>));
        }

        /// Binds a const class method
        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE void Bind(C const *instance)
        {
            //invocationList_.push_back(std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, MethodPtr>));
            invocationList_.emplace_back(std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, MethodPtr>));
        }
#endif

#pragma endregion

#pragma region Find

    protected:
         MA_INLINE typename invocation_list_t::const_iterator Find_Internal(proxy_pair_t &&pair) const
        {
            return std::find(invocationList_.cbegin(), invocationList_.cend(), ::std::forward<proxy_pair_t>(pair));
        }

    public:
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE typename invocation_list_t::const_iterator Find(void) const
        {
            return Find_Internal(::std::move(std::make_pair(nullptr, &FunctionProxy<FunctionPtr>)));
        }

        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE typename invocation_list_t::const_iterator Find(C * instance) const
        {
            return Find_Internal(::std::move(std::make_pair(instance, &MethodProxy<C, MethodPtr>)));
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE typename invocation_list_t::const_iterator Find(C const * instance) const
        {
            return Find_Internal(::std::move(std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, MethodPtr>)));
        }

#pragma endregion

#pragma region IsBound

    protected:
         MA_INLINE bool IsBound_Internal(proxy_pair_t &&pair) const
        {
            return (Find_Internal(::std::forward<proxy_pair_t>(pair)) != invocationList_.cend());
        }

    public:
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE bool IsBound(void) const
        {
            //return (Find<FunctionPtr>() != invocationList_.cend());
            return (IsBound_Internal(::std::move(std::make_pair(nullptr, &FunctionProxy<FunctionPtr>))));
        }

        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE bool IsBound(C *instance) const
        {
            //return (Find<C, MethodPtr>(instance) != invocationList_.cend());
            return (IsBound_Internal(::std::move(std::make_pair(instance, &MethodProxy<C, MethodPtr>))));
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE bool IsBound(C const *instance) const
        {
            //return (Find<C, MethodPtr>(instance) != invocationList_.cend());
            return (IsBound_Internal(::std::move(std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, MethodPtr>))));
        }

#pragma endregion

#pragma region BindUnique

    protected:
         MA_INLINE void BindUnique_Internal(proxy_pair_t &&pair)
        {
            if (!IsBound_Internal(::std::forward<proxy_pair_t>(pair)))
            {
                //invocationList_.push_back(pair);
                invocationList_.emplace_back(pair);
            }
        }

    public:
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE void BindUnique(void)
        {
            //BindUnique_Internal(::std::move(std::make_pair<void *, ProxyFunctionPtr>(nullptr, &FunctionProxy<FunctionPtr>)));
            BindUnique_Internal(::std::move(std::make_pair(nullptr, &FunctionProxy<FunctionPtr>)));
        }

        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE void BindUnique(C *instance)
        {
            //BindUnique_Internal(::std::move(std::make_pair<void *, ProxyFunctionPtr>(instance, &MethodProxy<C, MethodPtr>)));
            BindUnique_Internal(::std::move(std::make_pair(instance, &MethodProxy<C, MethodPtr>)));
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE void BindUnique(C const *instance)
        {
            //BindUnique_Internal(::std::move(std::make_pair<void *, ProxyFunctionPtr>(const_cast<C *>(instance), &ConstMethodProxy<C, MethodPtr>)));
            BindUnique_Internal(::std::move(std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, MethodPtr>)));
        }

#pragma endregion

#pragma region UnbindAll

        /// Unbinds all bound function
        void UnbindAll(void)
        {
            invocationList_.clear();
        }

        /// Unbinds all free/static functions of type FunctionPtr
        template <R(*FunctionPtr)(Args...)>
        void UnbindAll(void)
        {
            invocationList_.remove(
                std::make_pair(nullptr, &FunctionProxy<FunctionPtr>)
            );
        }

        /// Unbinds all methods of type MethodPtr
        template <class C, R(C::*MethodPtr)(Args...)>
        void UnbindAll(C *instance)
        {
            invocationList_.remove(
                std::make_pair(instance, &MethodProxy<C, MethodPtr>)
            );
        }

        /// Unbinds all const methods of type MethodPtr
        template <class C, R(C::*MethodPtr)(Args...) const>
        void UnbindAll(C const *instance)
        {
            invocationList_.remove(
                std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, MethodPtr>)
            );
        }

#pragma endregion

#pragma region Unbind

        /// Unbinds a free function
        template <R(*FunctionPtr)(Args...)>
        void Unbind(void)
        {
            auto iter = Find<FunctionPtr>();
            if (iter != invocationList_.end())
            {
                invocationList_.erase(iter);
            }
        }

        /// Unbinds a class method
        template <class C, R(C::*MethodPtr)(Args...)>
        void Unbind(C *instance)
        {
            auto iter = Find<C, MethodPtr>(instance);
            if (iter != invocationList_.end())
            {
                invocationList_.erase(iter);
            }
        }

        /// Unbinds a const class method
        template <class C, R(C::*MethodPtr)(Args...) const>
        void Unbind(C const *instance)
        {
            auto iter = Find<C, MethodPtr>(instance);
            if (iter != invocationList_.end())
            {
                invocationList_.erase(iter);
            }
        }

#pragma endregion

#pragma region Make

        /// In order to make use of the RAII pattern
        /// A static factory method can be used to create delegates.
        template <R(*FunctionPtr)(Args...)>
        static MulticastDelegate Make(void)
        {
            MulticastDelegate<R(Args...)> delegate;
            delegate.Bind<FunctionPtr>();
            return std::move(delegate);
        }

        template <class C, R(C::*MethodPtr)(Args...)>
        static MulticastDelegate Make(C *instance)
        {
            MulticastDelegate<R(Args...)> delegate;
            delegate.Bind<C, MethodPtr>(instance);
            return std::move(delegate);
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
        static MulticastDelegate Make(C const *instance)
        {
            MulticastDelegate<R(Args...)> delegate;
            delegate.Bind<C, MethodPtr>(instance);
            return std::move(delegate);
        }

#pragma endregion

#pragma region Invoke

        /// Invokes the delegate
        template<typename TRet = R>
        std::enable_if_t<std::is_void<TRet>::value, void>
            Invoke(Args &&...args) const
        {
            // MA_ASSERT(m_stub.second != nullptr, "Cannot invoke unbound delegate. Call Bind() first.")();
            assert(!invocationList_.empty() && "Cannot Invoke unbound MulticastDelegate. Call Bind first.");

            for (proxy_pair_t proxy : invocationList_)
            {
                proxy.second(proxy.first, ::std::forward<Args>(args)...);
            }
            //return;
        }

        /// Invokes the delegate
        template<typename TRet = R>
        std::enable_if_t<!std::is_void<TRet>::value, TRet>
            Invoke(Args &&...args) const
        {
            // MA_ASSERT(m_stub.second != nullptr, "Cannot invoke unbound delegate. Call Bind() first.")();
            assert(!invocationList_.empty() && "Cannot Invoke unbound MulticastDelegate. Call Bind first.");

            TRet result;
            for (proxy_pair_t proxy : invocationList_)
            {
                result = proxy.second(proxy.first, ::std::forward<Args>(args)...);
                //result = std::invoke(proxy.second, proxy.first, ::std::forward<Args>(args)...);
            }
            return result;
        }

#pragma endregion

         MA_INLINE invocation_list_t const & GetInvocationList(void) const
        {
            return invocationList_;
        }

    private:
        invocation_list_t invocationList_;
        // TODO: implement as contiguous (fixed-size) array / (dynamic-size) vector for faster iteration when invoked
        //std::vector<MulticastDelegate> invocationList_;
    };

    //template<typename TFun, typename... TArgs>
    //auto Invoke(TFun api, TArgs&&... args) ->
    //    typename std::enable_if<
    //    !std::is_void<typename std::result_of<TFun(TArgs...)>::type>::value,
    //    typename std::result_of<TFun(TArgs...)>::type
    //    >::type
    //{
    //    auto result = api(std::forward<TArgs&&>(args)...);
    //    return result;
    //}

    //template<typename TFun, typename... TArgs>
    //auto Invoke(TFun api, TArgs&&... args) ->
    //    typename std::enable_if<
    //    std::is_void<typename std::result_of<TFun(TArgs...)>::type>::value,
    //    typename std::result_of<TFun(TArgs...)>::type
    //    >::type
    //{
    //    api(std::forward<TArgs&&>(args)...);
    //}
}
