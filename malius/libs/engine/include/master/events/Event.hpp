#pragma once

//#include <utility>
#include <functional>
#include <list>
#include <vector>
#include <cassert>

//#include "common/Common.hpp"
#include "malius/events/Delegate.hpp"

namespace ma
{
	namespace events
	{
		template <typename Signature>
		class Event {};

		template <typename R, typename... Args>
		class Event<R(Args...)>
		{
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

			//class Sink;

			//template <typename R, typename... Args>
			class /*Event<R(Args...)>::*/Sink
			{
				typedef R(*ProxyFunction)(void *, Args...);
				typedef std::pair<void *, ProxyFunction> proxy_pair_t;

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

				//// TODO: implement allocators / memory system
				//struct allocator {};
				Sink(size_t maxListeners /*, allocator alloc = */)
				{
					//m_listeners.reserve(maxListeners);
					// = ::std::vector<proxy_pair_t, ::std::allocator<proxy_pair_t>>();
					//m_listeners = {};
					m_begin = new proxy_pair_t[maxListeners]{};
					m_end = m_begin;
					m_capacity = m_begin + (maxListeners - 1);
				}

				~Sink(void)
				{
					//m_sinks.remove(this);
					delete[] m_begin;
					m_end = m_capacity = nullptr;
				}

				template <R(*Function)(Args...)>
				void AddListener(void)
				{
					try
					{
						if (m_end > m_capacity)
						{
							throw std::out_of_range("Max. number of listeners reached! Cannot add new listeners.");
						}
						m_end = &std::make_pair(static_cast<void*>(nullptr), &FunctionProxy<Function>);
						++m_end;
						//m_listeners.push_back(
						//    std::make_pair(nullptr, &FunctionProxy<Function>)
						//);
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
						if (m_end > m_capacity)
						{
							throw std::out_of_range("Max. number of listeners reached! Cannot add new listeners.");
						}
						m_end = &std::make_pair(static_cast<void*>(instance), &MethodProxy<C, Function>);
						++m_end;
						//m_listeners.push_back(
						//    std::make_pair(instance, &MethodProxy<C, Function>)
						//);
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
						if (m_end > m_capacity)
						{
							throw std::out_of_range("Max. number of listeners reached! Cannot add new listeners.");
						}
						m_end = &std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, Function>);
						++m_end;
						//m_listeners.push_back(
						//    std::make_pair(const_cast<C *>(instance), &ConstMethodProxy<C, Function>)
						//);
					}
					catch (std::exception ex)
					{
						// TODO: error/exception handling
					}
				}

				template <R(*Function)(Args...)>
				void RemoveListener(void)
				{
					assert(m_end != m_begin && "Cannot remove listener. No listeners bound.");
					for (proxy_pair_t* listener = m_begin; listener != m_end; ++listener)
					{
						if (&(*listener->second) == Function)
						{
							std::swap(listener, --m_end);
							m_end = { nullptr, nullptr };
							break;
						}
					}
					//m_listeners.remove(Function);
				}

				 MA_INLINE proxy_pair_t const * Begin(void) const { return m_begin; }

				 MA_INLINE proxy_pair_t const * End(void) const { return m_begin; }

				 MA_INLINE ptrdiff_t Capacity(void) const { return m_capacity - m_begin; }

				 MA_INLINE ptrdiff_t Size(void) const { return m_end - m_begin; }

			protected:

				//std::vector<proxy_pair_t> m_listeners;
				//proxy_pair_t* m_listeners;
				proxy_pair_t* m_begin;
				proxy_pair_t* m_end;
				proxy_pair_t* m_capacity;
			};

			void Bind(Sink* sink)
			{
				m_sinks.push_back(sink);
			}

			void Unbind(Sink* sink)
			{
				m_sinks.remove(&sink);
			}

			/// Invokes the delegate
			// Broadcast
			void Signal(Args... args) const
			{
				// MA_ASSERT(m_stub.second != nullptr, "Cannot invoke unbound delegate. Call Bind() first.")();
				assert(!m_sinks.empty() && "Cannot invoke unbound Delegate. Call Bind() first.");

				for (auto it = m_sinks.begin(); it != m_sinks.end(); ++it)
				{
					Sink /*const*/* sink = *it;
					for (auto* proxy_pair = sink->Begin(); proxy_pair != sink->End(); ++proxy_pair)
					{
						proxy_pair->second(proxy_pair->first, std::forward<Args>(args)...);
					}

					//for (auto proxy : sink->m_listeners)
					//{
					//    proxy.second(proxy.first, std::forward<Args>(args)...);
					//}
				}
			}

		private:
			std::list<Sink*> m_sinks;
			//std::shared_ptr<Sink> test;
			//std::list<std::pair<void*, ProxyFunctionPtr>> m_listeners;
		};
	}
}
