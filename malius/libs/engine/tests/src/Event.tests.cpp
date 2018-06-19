// external libraries
#include <gtest/gtest.h>

// tested libraries
//#include <common/Config.hpp>
//#include <debugbreak/debugbreak.h>

#include "DelegateTestedClass.hpp"
#include <malius/events/Event.hpp>

//#include "event_system/EventSink.hpp"

namespace ma
{
	namespace test
	{
		namespace events
		{
			/// Tests the Bind overloads
			TEST(Event, Bind)
			{
				// Reference: http://gameenginegems.com/geg3/geg3-chapter13.zip
				// TODO: https://blog.molecular-matters.com/2011/09/19/generic-type-safe-delegates-and-events-in-c/?replytocom=231#respond
				// TODO: https://blog.molecular-matters.com/2011/08/12/a-safer-static_cast/

#pragma region
			// delegate with zero arguments
				{
					typedef ma::events::Event<int(int)> TestEvent;
					TestEvent event;
					//event.Bind<&Func0>();
					TestEvent::Sink sink(7);

					sink.AddListener<&ma::test::events::FuncInt1Arg>();

					DelegateTestedClass c;
					sink.AddListener<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&c);

					event.Signal(7);

					event.Bind(&sink);

					event.Signal(13);

					EXPECT_TRUE(true);

					//EXPECT_NO_FATAL_FAILURE(event.Invoke(););
				}
#pragma endregion

				//#pragma region
				//            // delegate with one argument
				//            {
				//                typedef Event<int(int)> TestEvent;
				//                TestEvent event;
				//
				//                // function
				//                event.Bind<&Func1>();
				//                int result = event.Invoke(10);
				//
				//                EXPECT_EQ(result, 20);
				//
				//                // method
				//                DelegateTestedClass t;
				//                event.Bind<DelegateTestedClass, &DelegateTestedClass::Func1>(&t);
				//                result = event.Invoke(1);
				//
				//                EXPECT_EQ(result, 21);
				//
				//                // const method
				//                const DelegateTestedClass ct;
				//                event.Bind<DelegateTestedClass, &DelegateTestedClass::Func1>(&ct);
				//                result = event.Invoke(1);
				//
				//                EXPECT_EQ(result, 31);
				//            }
				//#pragma endregion
				//
				//#pragma region
				//            // delegate with two arguments
				//            {
				//                typedef Event<float(float, float)> TestEvent;
				//                TestEvent event;
				//
				//                // function
				//                event.Bind<&Func2>();
				//                float result = event.Invoke(10.0f, 2.0f);
				//
				//                EXPECT_EQ(result, 20.0f);
				//
				//                // method
				//                DelegateTestedClass t;
				//                event.Bind<DelegateTestedClass, &DelegateTestedClass::Func2>(&t);
				//                result = event.Invoke(2.0f, 5.0f);
				//
				//                EXPECT_EQ(result, 7.0f);
				//
				//                // const method
				//                const DelegateTestedClass ct;
				//                event.Bind<DelegateTestedClass, &DelegateTestedClass::Func2>(&ct);
				//                result = event.Invoke(20.0f, 7.0f);
				//
				//                EXPECT_EQ(result, 13.0f);
				//            }
				//#pragma endregion
				//#pragma region
				//            // delegate to static member function
				//            {
				//                typedef Event<int()> TestEvent;
				//                TestEvent event;
				//
				//                // static member function
				//                event.Bind<&DelegateTestedClass::Func7>();
				//                int result = event.Invoke();
				//
				//                EXPECT_EQ(result, 7);
				//
				//                // returning private member
				//                DelegateTestedClass t;
				//                event.Bind<DelegateTestedClass, &DelegateTestedClass::Func13>(&t);
				//                result = event.Invoke();
				//
				//                EXPECT_EQ(result, 13);
				//
				//                // returning private member
				//                const DelegateTestedClass ct;
				//                event.Bind<DelegateTestedClass, &DelegateTestedClass::Func13>(&ct);
				//                result = event.Invoke();
				//
				//                EXPECT_EQ(result, 13);
				//            }
				//#pragma endregion
			}

			//        TEST(Delegate, Make)
			//        {
			//#pragma region
			//            // function
			//            {
			//                // ACT
			//                auto delegate = Event<int(int)>::Make<&Func1>();
			//
			//                // ASSERT
			//                int result = delegate.Invoke(7);
			//                EXPECT_EQ(result, 17);
			//            }
			//#pragma endregion
			//
			//#pragma region
			//            // method
			//            {
			//                // ARRANGE
			//                DelegateTestedClass t;
			//
			//                // ACT
			//                auto delegate = Event<int(int)>::Make<DelegateTestedClass, &DelegateTestedClass::Func1>(&t);
			//
			//                // ASSERT
			//                int result = delegate.Invoke(7);
			//                EXPECT_EQ(result, 27);
			//            }
			//#pragma endregion
			//
			//#pragma region
			//            // const method
			//            {
			//                // ARRANGE
			//                const DelegateTestedClass ct;
			//
			//                // ACT
			//                auto delegate = Event<int(int)>::Make<DelegateTestedClass, &DelegateTestedClass::Func1>(&ct);
			//
			//                // ASSERT
			//                int result = delegate.Invoke(7);
			//                EXPECT_EQ(result, 37);
			//            }
			//#pragma endregion
			//        }



			class DirectoryWatcher
			{
			public:
				typedef ma::events::Event<void(void)> ActionEvent;

				void Bind(ActionEvent::Sink* sink)
				{
					actionEvent.Bind(sink);
				}
			private:
				ActionEvent actionEvent;
			};


			//        TEST(Delegate, SingleArgumentConstructor)
			//        {
			//#pragma region
			//            {
			//                // store some event listeners in a sink
			//                DirectoryWatcher::ActionEvent::Sink eventSink;
			//                eventSink.AddListener<&ConfigHotReloader::OnAction>();
			//                eventSink.AddListener<&TextureReloader::OnAction>();
			//                eventSink.AddListener<&ResourceManager::OnAction>();
			//                eventSink.AddListener<&User_OnFileAction>();  // some user-defined function
			//
			//                // hook them to the directory watcher
			//                DirectoryWatcher directoryWatcher(/*currentDirectory*/);
			//                directoryWatcher.Bind(&eventSink);
			//
			//                // tick the directory watcher once a frame
			//                directoryWatcher.Tick();
			//
			//
			//
			//
			//
			//
			//                struct ConfigHotReloader
			//                {
			//                    
			//                };
			//
			//                // someplace else:
			//                ConfigHotReloader configReloader;
			//
			//                // setting up the sink
			//                DirectoryWatcher::ActionEvent::Sink eventSink(applicationAllocator, 16);
			//                eventSink.AddListener(&configReloader);
			//
			//
			//
			//
			//
			//            }
			//#pragma endregion
			//        }
		}
	}
}
