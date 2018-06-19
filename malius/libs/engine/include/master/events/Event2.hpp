#pragma once

//#include <utility>
#include <functional>
#include <list>
#include <vector>

#include "common/Common.hpp"
#include "malius/events/Delegate.hpp"

namespace ma
{
    template <typename Signature>
    class Event {};

    template <typename R, typename... Args>
    class Event<R(Args...)>
    {
        typedef R(*ProxyFunction)(void *, Args...);  // function ptr

                                                     // turns a free function into our internal function proxy
        template <R(*Function)(Args...)>
        static  MA_INLINE R FunctionProxy(void *, Args... args)
        {
            // we don't need the instance pointer because we're dealing with free functions
            return (Function)(std::forward<Args>(args)...);
        }

        // turns a member function into our internal function proxy
        template <class C, R(C::*Function)(Args...)>
        static  MA_INLINE R MethodProxy(void *instance, Args... args)
        {
            return (static_cast<C *>(instance)->*Function)(std::forward<Args>(args)...);
        }

        template <class C, R(C::*Function)(Args...) const>
        static  MA_INLINE R ConstMethodProxy(void *instance, Args... args)
        {
            return (static_cast<C const *>(instance)->*Function)(std::forward<Args>(args)...);
        }

    public:
        //        Event(void)
        //            : instance_(nullptr)
        //            , proxyFuncPtr_(nullptr)
        //        {
        //        }
        //
        //        /// Binds a free function
        //        template <R(*Function)(Args...)>
        //        void Bind(void)
        //        {
        //            instance_ = nullptr;
        //            proxyFuncPtr_ = &FunctionProxy<Function>;
        //        }
        //
        //#if defined(_MSC_VER) && (_MSC_VER < 1800)
        //        /// The reason you cannot call both methods Bind is due to overload resolution.
        //        /// Each instance can implicitly be converted into a const C*, 
        //        /// so the compiler will never try to use the first overload. 
        //        /// We need to force the compiler into only using the non-const overload 
        //        /// if the template argument is a non-const member function, and vice versa.
        //        /// By introducing two helpers called NonConstWrapper and ConstWrapper, we achieve two things:
        //        /// 1) Both Bind methods are now truly different overloads, taking different arguments.
        //        /// 2) By using non-explicit constructors in our helpers, the arguments need to always undergo implicit conversion.
        //        /// Because the template argument Function is part of the function argument (so to say), 
        //        /// only non-const member functions can be converted into a NonConstWrapper temporary, 
        //        /// and const member functions need to take the ConstWrapper overload.
        //        template <class C, R(C::*Function)(Args...)>
        //        struct NonConstWrapper
        //        {
        //            NonConstWrapper(C* instance)
        //                : instance_(instance)
        //            {
        //            }
        //
        //            C* instance_;
        //        };
        //
        //        template <class C, R(C::*Function)(Args...) const>
        //        struct ConstWrapper
        //        {
        //            ConstWrapper(const C* instance)
        //                : instance_(instance)
        //            {
        //            }
        //
        //            const C* instance_;
        //        };
        //
        //        /// Binds a class method
        //        template <class C, R(C::*Function)(Args...)>
        //        void Bind(NonConstWrapper<C, Function> wrapper)
        //        {
        //            m_stub.first.as_void = wrapper.instance_;
        //            m_stub.second = &MethodProxy<C, Function>;
        //        }
        //
        //        /// Binds a const class method
        //        template <class C, R(C::*Function)(Args...) const>
        //        void Bind(ConstWrapper<C, Function> wrapper)
        //        {
        //            m_stub.first.as_void_const = wrapper.instance_;
        //            m_stub.second = &ConstMethodProxy<C, Function>;
        //        }
        //#else
        //        /// Binds a class method
        //        template <class C, R(C::*Function)(Args...)>
        //        void Bind(C *instance)
        //        {
        //            instance_ = instance;
        //            proxyFuncPtr_ = &MethodProxy<C, Function>;
        //        }
        //
        //        /// Binds a const class method
        //        template <class C, R(C::*Function)(Args...) const>
        //        void Bind(C const *instance)
        //        {
        //            instance_ = const_cast<C *>(instance);
        //            proxyFuncPtr_ = &ConstMethodProxy<C, Function>;
        //        }
        //#endif
        //
        //        /// In order to make use of the RAII pattern
        //        /// A static factory method can be used to create delegates.
        //        template <R(*Function)(Args...)>
        //        //function for making a delegate object
        //        static Event Make(void)
        //        {
        //            Event<R(Args...)> event;
        //            event.Bind<Function>();
        //            return std::move(event);
        //        }
        //
        //        template <class C, R(C::*Function)(Args...) const>
        //        //function for making a delegate object
        //        static Event Make(C const *instance)
        //        {
        //            Event<R(Args...)> event;
        //            event.Bind<C, Function>(instance);
        //            return std::move(event);
        //        }
        //
        //        template <class C, R(C::*Function)(Args...)>
        //        //function for making a delegate object
        //        static Event Make(C *instance)
        //        {
        //            Event<R(Args...)> event;
        //            event.Bind<C, Function>(instance);
        //            return std::move(event);
        //        }
        //
        //        /// Invokes the delegate
        //        R Invoke(Args... args) const
        //        {
        //            // MA_ASSERT(m_stub.second != nullptr, "Cannot invoke unbound event. Call Bind() first.")();
        //            assert((proxyFuncPtr_ != nullptr) && "Cannot invoke unbound Event. Call Bind() first.");
        //            return proxyFuncPtr_(instance_, std::forward<Args>(args)...);
        //        }

        struct Sink
        {
            //// TODO: implement allocators / memory system
            //struct allocator {};
            //Sink(allocator alloc, size_t maxListeners)
            //{
            //    m_listeners[maxListeners] = { nullptr };
            //}

            template <R(*Function)(Args...)>
            void AddListener(void)
            {
                try
                {
                    m_listeners.push_back(
                        std::make_pair(nullptr, &FunctionProxy<Function>)
                    );
                }
                catch (std::exception ex)
                {
                    // TODO: error/exception handling
                }
            }

            template <class C, R(C::*Function)(Args...)>
            void AddListener(C *instance)
            {
                try
                {
                    m_listeners.push_back(
                        std::make_pair(instance, &MethodProxy<C, Function>)
                    );
                }
                catch (std::exception ex)
                {
                    // TODO: error/exception handling
                }
            }

            template <class C, R(C::*Function)(Args...) const>
            void AddListener(C const *instance)
            {
                try
                {
                    m_listeners.push_back(
                        std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, Function>)
                    );
                }
                catch (std::exception ex)
                {
                    // TODO: error/exception handling
                }
            }

            template <R(*Function)(Args...)>
            void RemoveListener(void)
            {
                try {
                    m_listeners.remove(Function);
                }
                catch (std::exception ex)
                {
                    // TODO: error/exception handling
                }
            }

            // TODO: make array/vector
            std::list<std::pair<void*, ProxyFunction>> m_listeners;
        };

        void Bind(Sink* sink)
        {
            // bind sink
            m_sinks.push_back(sink);
            //m_sinks2.push_back(sink->m_listeners);
        }

    private:
        //void *instance_;
        //ProxyFunctionPtr proxyFuncPtr_;
        std::vector<Sink*> m_sinks;
        //std::vector<std::list<std::pair<void*, ProxyFunctionPtr>>> m_sinks2;
        //std::list<std::pair<void*, ProxyFunctionPtr>> m_listeners;
    };
}
