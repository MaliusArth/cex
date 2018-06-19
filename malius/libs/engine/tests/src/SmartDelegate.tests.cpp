// external libraries
#include <gtest/gtest.h>

// tested libraries
//#include <common/Config.hpp>
//#include <debugbreak/debugbreak.h>

#include "DelegateTestedClass.hpp"
#include <malius/events/SmartDelegate.hpp>

// Reference: http://gameenginegems.com/geg3/geg3-chapter13.zip
// TODO: https://blog.molecular-matters.com/2011/09/19/generic-type-safe-delegates-and-events-in-c/?replytocom=231#respond
// TODO: https://blog.molecular-matters.com/2011/08/12/a-safer-static_cast/

namespace ma
{
	namespace test
	{
		namespace events
		{
			/// Tests the Bind overloads
			TEST(SmartDelegate, Bind)
			{
#pragma region  Invoke without return value

#pragma region  Invoke function with zero arguments
				{
					// ARRANGE
					typedef SmartDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncVoid0Args>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(t);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(ct);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region  Invoke function with one argument
				{
					// ARRANGE
					typedef SmartDelegate<void(int)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncVoid1Arg>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid1ArgStatic>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(t);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(ct);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region  Invoke function with two arguments
				{
					// ARRANGE
					typedef SmartDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncVoid2Args>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid2ArgsStatic>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(t);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(ct);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke with return value

#pragma region  Invoke function with zero arguments
				{
					// ARRANGE
					typedef SmartDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncInt0Args>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncInt0ArgsStatic>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(t);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(ct);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region  Invoke function with one argument
				{
					// ARRANGE
					typedef SmartDelegate<int(int)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncInt1Arg>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncInt1ArgStatic>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(t);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(ct);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region  Invoke function with two arguments
				{
					// ARRANGE
					typedef SmartDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncFloat2Args>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncFloat2ArgsStatic>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(t);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(ct);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma endregion
			}

			TEST(SmartDelegate, Make)
			{
#pragma region Make with function
				{
					// ACT
					auto delegate = SmartDelegate<void(void)>::Make<&FuncVoid0Args>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
				}
#pragma endregion

#pragma region Make with static member function
				{
					// ACT
					auto delegate = SmartDelegate<void(int)>::Make<&DelegateTestedClass::FuncVoid1ArgStatic>();

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
				}
#pragma endregion

#pragma region  Make with method
				{
					// ARRANGE
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// ACT
					auto delegate = SmartDelegate<int(int)>::Make<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(t);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
				}
#pragma endregion

#pragma region  Make with const method
				{
					// ARRANGE
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// ACT
					auto delegate = SmartDelegate<float(float, float)>::Make<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(ct);

					// ASSERT
					EXPECT_TRUE(delegate.IsBound());  // bool()
				}
#pragma endregion
			}

			TEST(SmartDelegate, Invoke)
			{
#pragma region  Invoke without return value

#pragma region  Invoke with no bound functions
				{
					typedef SmartDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					EXPECT_DEATH(delegate.Invoke(), "Cannot Invoke unbound SmartDelegate. Call Bind first.");
				}
#pragma endregion

#pragma region  Invoke function with zero arguments

#pragma region function
				{
					// ARRANGE
					typedef SmartDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncVoid0Args>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region static member function
				{
					// ARRANGE
					typedef SmartDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region method
				{
					// ARRANGE
					typedef SmartDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region const method
				{
					// ARRANGE
					typedef SmartDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with one argument

#pragma region function
				{
					// ARRANGE
					typedef SmartDelegate<void(int)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncVoid1Arg>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region static member function
				{
					// ARRANGE
					typedef SmartDelegate<void(int)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid1ArgStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region method
				{
					// ARRANGE
					typedef SmartDelegate<void(int)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region const method
				{
					// ARRANGE
					typedef SmartDelegate<void(int)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with two arguments

#pragma region  function
				{
					// ARRANGE
					typedef SmartDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncVoid2Args>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef SmartDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid2ArgsStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef SmartDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef SmartDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region  Invoke with return value

#pragma region  Invoke with no bound functions
				{
					typedef SmartDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					int result = -100;
					EXPECT_DEATH(result = delegate.Invoke(), "Cannot Invoke unbound SmartDelegate. Call Bind first.");
					EXPECT_EQ(result, -100);
				}
#pragma endregion

#pragma region  Invoke function with zero arguments

#pragma region  function
				{
					// ARRANGE
					typedef SmartDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncInt0Args>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, -1);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef SmartDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncInt0ArgsStatic>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 7);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef SmartDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(t);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 0);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef SmartDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(ct);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 1);
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with one argument

#pragma region  function
				{
					// ARRANGE
					typedef SmartDelegate<int(int)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncInt1Arg>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 10);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef SmartDelegate<int(int)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncInt1ArgStatic>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 70);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef SmartDelegate<int(int)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(t);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 20);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef SmartDelegate<int(int)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(ct);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 30);
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with two arguments

#pragma region  function
				{
					// ARRANGE
					typedef SmartDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncFloat2Args>();

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(10.0f, 3.0f));
					EXPECT_EQ(result, 7.0f);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef SmartDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncFloat2ArgsStatic>();

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(10.0f, 2.0f));
					EXPECT_EQ(result, 5.0f);
				}
#pragma endregion

#pragma region method
				{
					// ARRANGE
					typedef SmartDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(t);

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(4.0f, 3.0f));
					EXPECT_EQ(result, 7.0f);
				}
#pragma endregion

#pragma region const method
				{
					// ARRANGE
					typedef SmartDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;
					std::shared_ptr<DelegateTestedClass const> ct = std::make_shared<DelegateTestedClass const>();

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(ct);

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(2.0f, 7.0f));
					EXPECT_EQ(result, 14.0f);
				}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region dangling pointer
				{
					std::shared_ptr<DelegateTestedClass> t = std::make_shared<DelegateTestedClass>();

					auto delegate = SmartDelegate<int(void)>::Make<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(t);

					int result = -100;

					EXPECT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 0);

					t.reset();

					EXPECT_DEATH(result = delegate.Invoke(), "The instance has expired!");
					EXPECT_EQ(result, 0);
				}
#pragma endregion
			}
		}
	}
}
