#pragma once

// standard libraries
#include <utility>
#include <algorithm>
#include <functional>
#include <list>
#include <cassert>
#include <memory>
//#include <initializer_list>

#include <malius/core/lang.hpp>

namespace ma
{
    template <typename Signature>
    class SmartMulticastDelegate;

    template <typename R, typename ...Args>
    class SmartMulticastDelegate<R(Args...)>
    {
        // function ptr
        typedef R(*ProxyFunctionPtr)(std::weak_ptr<void> const &, Args &&...);
        typedef std::pair<std::weak_ptr<void>, ProxyFunctionPtr> proxy_pair_t;
        typedef std::list<proxy_pair_t> invocation_list_t;

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
        SmartMulticastDelegate(void) = default;
        //SmartMulticastDelegate(void)
        //    //: instance_(nullptr)
        //    : weakInstance_()
        //    , proxyFuncPtr_(nullptr)
        //{
        //}

        // deconstructor
        ~SmartMulticastDelegate(void)
        {
            UnbindAll();
        }

        // copy constructor
        SmartMulticastDelegate(SmartMulticastDelegate const &) = default;

        // move constructor
        SmartMulticastDelegate(SmartMulticastDelegate &&) = default;

        // copy assignment operator
        SmartMulticastDelegate& operator=(SmartMulticastDelegate const &) = default;

        // move assignment operator
        SmartMulticastDelegate& operator=(SmartMulticastDelegate &&) = default;

        //// copy assignment operator
        //SmartDelegate& operator=(SmartDelegate const & other)
        //{
        //    weakInstance_ = other.weakInstance_;
        //    proxyFuncPtr_ = other.proxyFuncPtr_;
        //    return *this;
        //}

        //// move assignment operator
        //SmartDelegate& operator=(SmartDelegate&& other)
        //{
        //    weakInstance_ = other.weakInstance_;
        //    proxyFuncPtr_ = other.proxyFuncPtr_;
        //    other.weakInstance_.reset();
        //    other.proxyFuncPtr_ = nullptr;
        //    return *this;
        //}

        //// alternatively, replace both assignment operators with 
        ////  SmartDelegate& operator=(SmartDelegate other)
        ////  {
        ////      std::swap(weakInstance_, other.weakInstance_);
        ////      std::swap(proxyFuncPtr_, other.proxyFuncPtr_);
        ////      return *this;
        ////  }

#pragma region Bind

        /// Binds a free function
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE void Bind(void)
        {
            invocationList_.emplace_back(std::make_pair(std::weak_ptr<void>(), &FunctionProxy<FunctionPtr>));
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
         MA_INLINE void Bind(std::shared_ptr<C> const & instance)
        {
            invocationList_.emplace_back(std::make_pair(instance, &MethodProxy<C, MethodPtr>));
        }

        /// Binds a const class method
        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE void Bind(std::shared_ptr<C const> const & instance)
        {
            invocationList_.emplace_back(std::make_pair(std::const_pointer_cast<C>(instance), &ConstMethodProxy<C, MethodPtr>));
        }
#endif

#pragma endregion

#pragma region Find

    //protected:
    //     MA_INLINE typename invocation_list_t::const_iterator Find_Internal(proxy_pair_t &&pair) const
    //    {
    //        //return std::find(invocationList_.cbegin(), invocationList_.cend(), ::std::forward<proxy_pair_t>(pair));

    //        return std::find_if(invocationList_.cbegin(), invocationList_.cend(),
    //            [&](proxy_pair_t const & tested) {
    //            return ((tested.second == pair.second) && (!tested.first.owner_before(pair.first) && !pair.first.owner_before(tested.first)));
    //        }
    //        );
    //    }

    public:
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE typename invocation_list_t::const_iterator Find(void) const
        {
            //return Find_Internal(::std::move(std::make_pair(std::weak_ptr<void>(), &FunctionProxy<FunctionPtr>)));

            return std::find_if(invocationList_.cbegin(), invocationList_.cend(),
                [](proxy_pair_t const & tested) {
                return (tested.second == &FunctionProxy<FunctionPtr>);
            }
            );
        }

        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE typename invocation_list_t::const_iterator Find(std::shared_ptr<C> const & instance) const
        {
            //return Find_Internal(::std::move(std::make_pair(instance, &MethodProxy<C, MethodPtr>)));

            auto test = invocationList_.cbegin()->first.owner_before(instance);
            auto test2 = instance.owner_before(invocationList_.cbegin()->first);

            return std::find_if(invocationList_.cbegin(), invocationList_.cend(),
                [&](proxy_pair_t const & tested) {
                return ((tested.second == &MethodProxy<C, MethodPtr>) && (!tested.first.owner_before(instance) && !instance.owner_before(tested.first)));
            }
            );
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE typename invocation_list_t::const_iterator Find(std::shared_ptr<C const> const & instance) const
        {
            //return Find_Internal(::std::move(std::make_pair(std::const_pointer_cast<C>(instance), &ConstMethodProxy<C, MethodPtr>)));

            return std::find_if(invocationList_.cbegin(), invocationList_.cend(),
                [&](proxy_pair_t const & tested) {
                return ((tested.second == &ConstMethodProxy<C, MethodPtr>) && (!tested.first.owner_before(instance) && !instance.owner_before(tested.first)));
            }
            );
        }

#pragma endregion

#pragma region IsBound

    //protected:
    //     MA_INLINE bool IsBound_Internal(proxy_pair_t &&pair) const
    //    {
    //        return (Find_Internal(::std::forward<proxy_pair_t>(pair)) != invocationList_.cend());
    //    }

    public:
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE bool IsBound(void) const
        {
            return (Find<FunctionPtr>() != invocationList_.cend());
            //return (IsBound_Internal(::std::move(std::make_pair(std::weak_ptr<void>(), &FunctionProxy<FunctionPtr>))));
        }

        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE bool IsBound(std::shared_ptr<C> const & instance) const
        {
            return (Find<C, MethodPtr>(instance) != invocationList_.cend());
            //return (IsBound_Internal(::std::move(std::make_pair(instance, &MethodProxy<C, MethodPtr>))));
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE bool IsBound(std::shared_ptr<C const> const & instance) const
        {
            return (Find<C, MethodPtr>(instance) != invocationList_.cend());
            //return (IsBound_Internal(::std::move(std::make_pair(std::const_pointer_cast<C>(instance), &ConstMethodProxy<C, MethodPtr>))));
        }

#pragma endregion

#pragma region BindUnique

    //protected:
    //     MA_INLINE void BindUnique_Internal(proxy_pair_t && pair)
    //    {
    //        if (!IsBound_Internal(::std::forward<proxy_pair_t>(pair)))
    //        {
    //            //invocationList_.push_back(pair);
    //            invocationList_.emplace_back(pair);
    //        }
    //    }

    public:
        template <R(*FunctionPtr)(Args...)>
         MA_INLINE void BindUnique(void)
        {
            //BindUnique_Internal(::std::move(std::make_pair(std::weak_ptr<void>(), &FunctionProxy<FunctionPtr>)));

            if (!IsBound<FunctionPtr>())
            {
                invocationList_.emplace_back(std::make_pair(std::weak_ptr<void>(), &FunctionProxy<FunctionPtr>));
            }
        }

        template <class C, R(C::*MethodPtr)(Args...)>
         MA_INLINE void BindUnique(std::shared_ptr<C> const & instance)
        {
            //BindUnique_Internal(::std::move(std::make_pair(instance, &MethodProxy<C, MethodPtr>)));

            if (!IsBound<C, MethodPtr>(instance))
            {
                invocationList_.emplace_back(std::make_pair(instance, &MethodProxy<C, MethodPtr>));
            }
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
         MA_INLINE void BindUnique(std::shared_ptr<C const> const & instance)
        {
            //BindUnique_Internal(::std::move(std::make_pair(std::const_pointer_cast<C>(instance), &ConstMethodProxy<C, MethodPtr>)));

            if (!IsBound<C, MethodPtr>(instance))
            {
                invocationList_.emplace_back(std::make_pair(std::const_pointer_cast<C>(instance), &ConstMethodProxy<C, MethodPtr>));
            }
        }

#pragma endregion

#pragma region UnbindAll

        /// Unbinds all bound function
        void UnbindAll(void)
        {
            invocationList_.clear();
        }

        //protected:
        // MA_INLINE void UnbindAll_Internal(proxy_pair_t && pair)
        //{
        //    // erase-remove idiom: https://en.wikipedia.org/wiki/Erase-remove_idiom
        //    invocationList_.erase(
        //        std::remove_if(invocationList_.begin(), invocationList_.end(),
        //            [&](proxy_pair_t const & tested) {
        //                return ((tested.second == pair.second) && (tested.first.owner_before(pair.first) && pair.first.owner_before(tested.first)));
        //            }
        //        ),
        //        invocationList_.end()
        //    );
        //}

        public:
        /// Unbinds all free/static functions of type FunctionPtr
        template <R(*FunctionPtr)(Args...)>
        void UnbindAll(void)
        {
            //UnbindAll_Internal(std::move(std::make_pair(std::weak_ptr<void>(), &FunctionProxy<FunctionPtr>)));

            // erase-remove idiom: https://en.wikipedia.org/wiki/Erase-remove_idiom
            invocationList_.erase(
                std::remove_if(invocationList_.begin(), invocationList_.end(),
                    [](proxy_pair_t const & tested) {
                return tested.second == &FunctionProxy<FunctionPtr>;
            }
                ),
                invocationList_.end()
                );

            //invocationList_.erase(
            //    std::remove_if(invocationList_.begin(), invocationList_.end(),
            //        ProxyCompare<FunctionPtr>()
            //    ),
            //    invocationList_.end()
            //    );
        }

        /// Unbinds all methods of type MethodPtr
        template <class C, R(C::*MethodPtr)(Args...)>
        void UnbindAll(std::shared_ptr<C> const & instance)
        {
            //UnbindAll_Internal(std::move(std::make_pair(instance, &MethodProxy<C, MethodPtr>)));

            // erase-remove idiom: https://en.wikipedia.org/wiki/Erase-remove_idiom
            invocationList_.erase(
                std::remove_if(invocationList_.begin(), invocationList_.end(),
                    [&](proxy_pair_t const & tested) {
                return ((tested.second == &MethodProxy<C, MethodPtr>) && (!tested.first.owner_before(instance) && !instance.owner_before(tested.first)));
            }
                ),
                invocationList_.end()
                );

            //invocationList_.erase(
            //    std::remove_if(invocationList_.begin(), invocationList_.end(),
            //        ProxyCompare<C, MethodPtr>(instance)
            //    ),
            //    invocationList_.end()
            //    );
        }

        /// Unbinds all const methods of type MethodPtr
        template <class C, R(C::*MethodPtr)(Args...) const>
        void UnbindAll(std::shared_ptr<C const> const & instance)
        {
            //UnbindAll_Internal(std::move(std::make_pair(std::const_pointer_cast<C>(instance), &ConstMethodProxy<C, MethodPtr>)));

            // erase-remove idiom: https://en.wikipedia.org/wiki/Erase-remove_idiom
            invocationList_.erase(
                std::remove_if(invocationList_.begin(), invocationList_.end(),
                    [&](proxy_pair_t const & tested) {
                        return ((tested.second == &ConstMethodProxy<C, MethodPtr>) && (!tested.first.owner_before(instance) && !instance.owner_before(tested.first)));
                    }
                ),
                invocationList_.end()
            );
        }

#pragma endregion

        //template<R(*FunctionPtr)(Args...)>
        //struct ProxyCompare
        //{
        //    //proxy_pair_t const & comparedItem;
        //    //ProxyCompare(proxy_pair_t const & compare)
        //    //    : comparedItem(compare)
        //    //{}

        //    bool operator()(proxy_pair_t const & b)
        //    {
        //        return b.second == &FunctionProxy<FunctionPtr>;
        //    }
        //};

        //template <class C, R(C::*MethodPtr)(Args...)>
        //struct ProxyCompare
        //{
        //    ProxyCompare(proxy_pair_t const & a)
        //        : a_(a)
        //    {}

        //    bool operator()(proxy_pair_t const & b)
        //    {
        //        return ((b.second == &MethodProxy<C, MethodPtr>) && (!b.first.owner_before(a_) && !a_.owner_before(b.first)));
        //    }

        //private:
        //    proxy_pair_t const & a_;
        //};

        //template <class C, R(C::*MethodPtr)(Args...) const>
        //struct ProxyCompare
        //{
        //    ProxyCompare(proxy_pair_t const & a)
        //        : a_(a)
        //    {}

        //    bool operator()(proxy_pair_t const & b)
        //    {
        //        return ((b.second == &ConstMethodProxy<C, MethodPtr>) && (!b.first.owner_before(a_) && !a_.owner_before(b.first)));
        //    }

        //private:
        //    proxy_pair_t const & a_;
        //};

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
        void Unbind(std::shared_ptr<C> const & instance)
        {
            auto iter = Find<C, MethodPtr>(instance);
            if (iter != invocationList_.end())
            {
                invocationList_.erase(iter);
            }
        }

        /// Unbinds a const class method
        template <class C, R(C::*MethodPtr)(Args...) const>
        void Unbind(std::shared_ptr<C const> const & instance)
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
        static SmartMulticastDelegate Make(void)
        {
            SmartMulticastDelegate<R(Args...)> delegate;
            delegate.Bind<FunctionPtr>();
            return std::move(delegate);
        }

        template <class C, R(C::*MethodPtr)(Args...)>
        static SmartMulticastDelegate Make(std::shared_ptr<C> const & instance)
        {
            SmartMulticastDelegate<R(Args...)> delegate;
            delegate.Bind<C, MethodPtr>(instance);
            return std::move(delegate);
        }

        template <class C, R(C::*MethodPtr)(Args...) const>
        static SmartMulticastDelegate Make(std::shared_ptr<C const> const & instance)
        {
            SmartMulticastDelegate<R(Args...)> delegate;
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
            assert(!invocationList_.empty() && "Cannot Invoke unbound SmartMulticastDelegate. Call Bind first.");

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
            assert(!invocationList_.empty() && "Cannot Invoke unbound SmartMulticastDelegate. Call Bind first.");

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
        //std::vector<SmartMulticastDelegate> invocationList_;
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
