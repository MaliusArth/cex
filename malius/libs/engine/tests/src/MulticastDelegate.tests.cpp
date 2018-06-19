// external libraries
#include <gtest/gtest.h>

// tested libraries
//#include <common/Config.hpp>
//#include <debugbreak/debugbreak.h>
//#include "log/Debug.hpp"
#include "DelegateTestedClass.hpp"
#include <malius/events/MulticastDelegate.hpp>

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
			TEST(MulticastDelegate, Bind)
			{
				bool result = false;
#pragma region  Bind function with zero arguments

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncInt0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncInt0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<&DelegateTestedClass::FuncInt0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncInt0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma endregion

#pragma region  Bind function with one argument

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncVoid1Arg>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid1Arg>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<&FuncVoid1Arg>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid1Arg>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid1ArgStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid1ArgStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<&DelegateTestedClass::FuncVoid1ArgStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid1ArgStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma endregion

#pragma region  Bind function with two arguments

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncFloat2Args>();

					// ASSERT
					result = delegate.IsBound<&FuncFloat2Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<&FuncFloat2Args>();

					// ASSERT
					result = delegate.IsBound<&FuncFloat2Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncFloat2ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncFloat2ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<&DelegateTestedClass::FuncFloat2ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncFloat2ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma endregion
			}

			TEST(MulticastDelegate, BindUnique)
			{
				bool result = false;
#pragma region  Bind then BindUnique

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.Bind<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// ACT
					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// ACT
					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma endregion

#pragma region  BindUnique then BindUnique

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.BindUnique<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// static member function
					delegate.BindUnique<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// ACT
					// method
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// ACT
					// const method
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);
				}
#pragma endregion

#pragma endregion

#pragma region  BindUnique then Bind

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// function
					delegate.BindUnique<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.Bind<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// ACT
					// static member function
					delegate.BindUnique<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// ACT
					// method
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma region const method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// ACT
					// const method
					delegate.BindUnique<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);
					EXPECT_TRUE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);
				}
#pragma endregion

#pragma endregion
			}

			TEST(MulticastDelegate, UnbindAll)
			{
#pragma region  UnbindAll without bound functions
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					EXPECT_EQ(delegate.GetInvocationList().size(), 0);

					// ACT
					delegate.UnbindAll();

					// ASSERT
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);
				}
#pragma endregion

#pragma region  UnbindAll with bound functions
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncVoid0Args>();

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// method
					DelegateTestedClass t;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// const method
					const DelegateTestedClass ct;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					EXPECT_EQ(delegate.GetInvocationList().size(), 4);

					// ACT
					delegate.UnbindAll();

					// ASSERT
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);
				}
#pragma endregion

#pragma region  UnbindAll<> without bound functions
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;
					const DelegateTestedClass ct;

					EXPECT_EQ(delegate.GetInvocationList().size(), 0);

					// ACT
					delegate.UnbindAll<&FuncVoid0Args>();
					delegate.UnbindAll<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					delegate.UnbindAll<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					delegate.UnbindAll<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ASSERT
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);
				}
#pragma endregion

#pragma region  UnbindAll<> with bound functions
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					bool result = false;

					// function
					delegate.Bind<&FuncVoid0Args>();

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// method
					DelegateTestedClass t;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// const method
					const DelegateTestedClass ct;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					EXPECT_EQ(delegate.GetInvocationList().size(), 4);

					// ACT
					delegate.UnbindAll<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 3);

					// ACT
					delegate.UnbindAll<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);

					// ACT
					delegate.UnbindAll<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 1);

					// ACT
					delegate.UnbindAll<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);
				}
#pragma endregion

#pragma region  UnbindAll<> with duplicate bound functions
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					bool result = false;

					// function
					delegate.Bind<&FuncVoid0Args>();
					delegate.Bind<&FuncVoid0Args>();

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// method
					DelegateTestedClass t;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// const method
					const DelegateTestedClass ct;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					EXPECT_EQ(delegate.GetInvocationList().size(), 8);

					// ACT
					delegate.UnbindAll<&FuncVoid0Args>();

					// ASSERT
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 6);

					// ACT
					delegate.UnbindAll<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 4);

					// ACT
					delegate.UnbindAll<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 2);

					// ACT
					delegate.UnbindAll<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);
					EXPECT_FALSE(result);
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);
				}
#pragma endregion
			}

			TEST(MulticastDelegate, Unbind)
			{
#pragma region  Unbind not bound functions
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					EXPECT_EQ(delegate.GetInvocationList().size(), 0);

					// ACT
					// function
					delegate.Unbind<&FuncVoid0Args>();

					// ASSERT
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);

					//ACT
					// static member function
					delegate.Unbind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);

					// ACT
					// method
					DelegateTestedClass t;
					delegate.Unbind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ASSERT
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);

					// ACT
					// const method
					const DelegateTestedClass ct;
					delegate.Unbind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ASSERT
					EXPECT_EQ(delegate.GetInvocationList().size(), 0);
				}
#pragma endregion

#pragma region  Unbind bound duplicate functions
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					bool result = false;

					// function
					delegate.Bind<&FuncVoid0Args>();
					delegate.Bind<&FuncVoid0Args>();

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// method
					DelegateTestedClass t;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// const method
					const DelegateTestedClass ct;
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					const auto &list = delegate.GetInvocationList();
					EXPECT_EQ(list.size(), 8);

					// ACT
					// function
					delegate.Unbind<&FuncVoid0Args>();

					// ASSERT
					EXPECT_EQ(list.size(), 7);
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_TRUE(result);

					// ACT
					// function
					delegate.Unbind<&FuncVoid0Args>();

					// ASSERT
					EXPECT_EQ(list.size(), 6);
					result = delegate.IsBound<&FuncVoid0Args>();
					EXPECT_FALSE(result);

					// ACT
					// static member function
					delegate.Unbind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					EXPECT_EQ(list.size(), 5);
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_TRUE(result);

					// ACT
					// static member function
					delegate.Unbind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ASSERT
					EXPECT_EQ(list.size(), 4);
					result = delegate.IsBound<&DelegateTestedClass::FuncVoid0ArgsStatic>();
					EXPECT_FALSE(result);

					// ACT
					// method
					delegate.Unbind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ASSERT
					EXPECT_EQ(list.size(), 3);
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					EXPECT_TRUE(result);

					// ACT
					// method
					delegate.Unbind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ASSERT
					EXPECT_EQ(list.size(), 2);
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);
					EXPECT_FALSE(result);

					// ACT
					// const method
					delegate.Unbind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ASSERT
					EXPECT_EQ(list.size(), 1);
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);
					EXPECT_TRUE(result);

					// ACT
					// const method
					delegate.Unbind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ASSERT
					EXPECT_EQ(list.size(), 0);
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);
					EXPECT_FALSE(result);
				}
#pragma endregion
			}

			TEST(MulticastDelegate, Make)
			{
				bool result = false;
#pragma region  Make with function
				{
					// ACT
					auto delegate = MulticastDelegate<int(int)>::Make<&FuncInt1Arg>();

					// ASSERT
					result = delegate.IsBound<&FuncInt1Arg>();
					EXPECT_TRUE(result);
				}
#pragma endregion

#pragma region  Make with static member function
				{
					// ACT
					auto delegate = MulticastDelegate<int(int)>::Make<&DelegateTestedClass::FuncInt1ArgStatic>();

					// ASSERT
					result = delegate.IsBound<&DelegateTestedClass::FuncInt1ArgStatic>();
					EXPECT_TRUE(result);
				}
#pragma endregion

#pragma region  Make with method
				{
					// ARRANGE
					DelegateTestedClass t;

					// ACT
					auto delegate = MulticastDelegate<int(int)>::Make<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&t);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&t);
					EXPECT_TRUE(result);
				}
#pragma endregion

#pragma region  Make with const method
				{
					// ARRANGE
					const DelegateTestedClass ct;

					// ACT
					auto delegate = MulticastDelegate<int(int)>::Make<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&ct);

					// ASSERT
					result = delegate.IsBound<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&ct);
					EXPECT_TRUE(result);
				}
#pragma endregion
			}

			TEST(MulticastDelegate, Invoke)
			{
#pragma region  Invoke without return value

#pragma region  Invoke with no bound functions
				{
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					EXPECT_DEATH(delegate.Invoke(), "Cannot Invoke unbound MulticastDelegate. Call Bind first.");
				}
#pragma endregion

#pragma region  Invoke function with zero arguments

#pragma region function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncVoid0Args>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE - duplicate
					delegate.Bind<&FuncVoid0Args>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region static member function
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE - duplicate
					delegate.Bind<&DelegateTestedClass::FuncVoid0ArgsStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region method
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma region const method
				{
					// ARRANGE
					typedef MulticastDelegate<void(void)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid0Args>(&ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke());
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with one argument

#pragma region function
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncVoid1Arg>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE - duplicate
					delegate.Bind<&FuncVoid1Arg>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region static member function
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid1ArgStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE - duplicate
					delegate.Bind<&DelegateTestedClass::FuncVoid1ArgStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region method
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma region const method
				{
					// ARRANGE
					typedef MulticastDelegate<void(int)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid1Arg>(&ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0));
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with two arguments

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncVoid2Args>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE - duplicate
					delegate.Bind<&FuncVoid2Args>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncVoid2ArgsStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE - duplicate
					delegate.Bind<&DelegateTestedClass::FuncVoid2ArgsStatic>();

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(&t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(&t);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<void(float, float)> TestDelegate;
					TestDelegate delegate;
					const DelegateTestedClass ct;

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(&ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncVoid2Args>(&ct);

					// ACT & ASSERT
					EXPECT_NO_FATAL_FAILURE(delegate.Invoke(0.0f, 0.0f));
				}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region  Invoke with return value

#pragma region  Invoke with no bound functions
				{
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					int result = -100;
					EXPECT_DEATH(result = delegate.Invoke(), "Cannot Invoke unbound MulticastDelegate. Call Bind first.");
					EXPECT_EQ(result, -100);
				}
#pragma endregion

#pragma region  Invoke function with zero arguments

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncInt0Args>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, -1);

					// ARRANGE - duplicate
					delegate.Bind<&FuncInt0Args>();

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, -1);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncInt0ArgsStatic>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 7);

					// ARRANGE - duplicate
					delegate.Bind<&DelegateTestedClass::FuncInt0ArgsStatic>();

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 7);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 0);

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&t);

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 0);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<int(void)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass const ct;

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 1);

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(&ct);

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke());
					EXPECT_EQ(result, 1);
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with one argument

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<int(int)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncInt1Arg>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 10);

					// ARRANGE - duplicate
					delegate.Bind<&FuncInt1Arg>();

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 10);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<int(int)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncInt1ArgStatic>();

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 70);

					// ARRANGE - duplicate
					delegate.Bind<&DelegateTestedClass::FuncInt1ArgStatic>();

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 70);
				}
#pragma endregion

#pragma region  method
				{
					// ARRANGE
					typedef MulticastDelegate<int(int)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&t);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 20);

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&t);

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 20);
				}
#pragma endregion

#pragma region  const method
				{
					// ARRANGE
					typedef MulticastDelegate<int(int)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass const ct;

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&ct);

					// ACT & ASSERT
					int result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 30);

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncInt1Arg>(&ct);

					// ACT & ASSERT
					result = -100;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(0));
					EXPECT_EQ(result, 30);
				}
#pragma endregion

#pragma endregion

#pragma region  Invoke function with two arguments

#pragma region  function
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;

					// function
					delegate.Bind<&FuncFloat2Args>();

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(10.0f, 3.0f));
					EXPECT_EQ(result, 7.0f);

					// ARRANGE - duplicate
					delegate.Bind<&FuncFloat2Args>();

					// ACT & ASSERT
					result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(10.0f, 3.0f));
					EXPECT_EQ(result, 7.0f);
				}
#pragma endregion

#pragma region  static member function
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;

					// static member function
					delegate.Bind<&DelegateTestedClass::FuncFloat2ArgsStatic>();

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(10.0f, 2.0f));
					EXPECT_EQ(result, 5.0f);

					// ARRANGE - duplicate
					delegate.Bind<&DelegateTestedClass::FuncFloat2ArgsStatic>();

					// ACT & ASSERT
					result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(10.0f, 2.0f));
					EXPECT_EQ(result, 5.0f);
				}
#pragma endregion

#pragma region method
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass t;

					// method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&t);

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(4.0f, 3.0f));
					EXPECT_EQ(result, 7.0f);

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&t);

					// ACT & ASSERT
					result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(4.0f, 3.0f));
					EXPECT_EQ(result, 7.0f);
				}
#pragma endregion

#pragma region const method
				{
					// ARRANGE
					typedef MulticastDelegate<float(float, float)> TestDelegate;
					TestDelegate delegate;
					DelegateTestedClass const ct;

					// const method
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&ct);

					// ACT & ASSERT
					float result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(2.0f, 7.0f));
					EXPECT_EQ(result, 14.0f);

					// ARRANGE - duplicate
					delegate.Bind<DelegateTestedClass, &DelegateTestedClass::FuncFloat2Args>(&ct);

					// ACT & ASSERT
					result = -100.0f;
					ASSERT_NO_FATAL_FAILURE(result = delegate.Invoke(2.0f, 7.0f));
					EXPECT_EQ(result, 14.0f);
				}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region dangling pointer
				{
					auto *t = new DelegateTestedClass();

					auto delegate = MulticastDelegate<int(void)>::Make<DelegateTestedClass, &DelegateTestedClass::FuncInt0Args>(t);

					delete t;

					int result = delegate.Invoke();
					//EXPECT_DEATH(delegate.Invoke());
					EXPECT_EQ(result, 0);
				}
#pragma endregion
			}
		}
	}
}
