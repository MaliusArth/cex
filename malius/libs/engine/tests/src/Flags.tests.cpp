// external libraries
#include <gtest/gtest.h>

// tested libraries
//#include <malius/Config.hpp>
#include "containers/Flags.hpp"
//#include <debugbreak/debugbreak.h>

#include "FlagsTest.hpp"

namespace ma
{
	namespace test
	{
		namespace flags
		{
			/// Tests the default c'tor.
			TEST_F(FlagsTest, DefaultConstructor)
			{
#pragma region
				// ASSERT
				EXPECT_FALSE(m_state0.IsAnySet());
#pragma endregion
			}

			/// Tests Flags<T>(T::Enum).
			TEST_F(FlagsTest, SingleArgumentConstructor)
			{
#pragma region
				// ASSERT
				//EXPECT_TRUE(m_state1.IsAnySet());
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state1.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Floating));
#pragma endregion
			}

#ifdef  MA_INIT_LISTS
			/// Tests Flags<T>(std::initializer_list<Enum>&& list).
			TEST_F(FlagsTest, InitListConstructor)
			{
#pragma region
				// ASSERT
				//EXPECT_TRUE(m_state2.IsAnySet());
				EXPECT_FALSE(m_state2.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state2.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state2.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state2.IsSet(PlayerState::Floating));
#pragma endregion
			}

			/// Tests Set(std::initializer_list<Enum>&& list).
			TEST_F(FlagsTest, InitListSet)
			{
#pragma region
				// ACT
				// set flag - type-safe!
				m_state0.Set({ PlayerState::Stunned, PlayerState::Floating });
				// ASSERT
				//EXPECT_TRUE(m_state0.IsAnySet());
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion
			}
#endif //  MA_INIT_LISTS

			/// Tests Set(T::Enum).
			TEST_F(FlagsTest, Set)
			{
#pragma region
				// ACT
				// set flag - type-safe!
				m_state0.Set(PlayerState::Killed);

				// ASSERT
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				// set flag - type-safe!
				m_state0.Set(PlayerState::Dazed);
				m_state0.Set(PlayerState::Floating);

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				// set flag - type-safe!
				m_state0.Set(PlayerState::Killed);

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				// set flag - type-safe!
				m_state0.Set(PlayerState::Stunned);

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				// set flag - type-safe!
				m_state0.Set(PlayerState::Floating);

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion
			}

			/// Tests Remove(T::Enum).
			TEST_F(FlagsTest, Remove)
			{
#pragma region
				// ARRANGE
				m_state1.Set(PlayerState::Floating);

				// ACT
				m_state1.Remove(PlayerState::Stunned);

				// ASSERT
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Dazed));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state1.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				m_state1.Remove(PlayerState::Stunned);

				// ASSERT
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Dazed));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state1.IsSet(PlayerState::Floating));
#pragma endregion
			}

			/// Tests Clear().
			TEST_F(FlagsTest, Clear)
			{
#pragma region
				// ACT
				m_state1.Clear();

				// ASSERT
				EXPECT_FALSE(m_state1.IsAnySet());
#pragma endregion

#pragma region
				// ACT
				m_state2.Clear();

				// ASSERT
				EXPECT_FALSE(m_state2.IsAnySet());
#pragma endregion
			}

			/// Tests AreAllSet().
			TEST_F(FlagsTest, AreAllSet)
			{
#pragma region
				// ACT & ASSERT
				EXPECT_FALSE(m_state0.AreAllSet());
#pragma endregion

#pragma region
				// ARRANGE
				m_state0.Set(PlayerState::Dazed);

				// ACT & ASSERT
				EXPECT_FALSE(m_state0.AreAllSet());
#pragma endregion

#pragma region
				m_state0.Set(PlayerState::Floating);

				// ACT & ASSERT
				EXPECT_FALSE(m_state0.AreAllSet());
#pragma endregion

#pragma region
				// ARRANGE
				m_state0.Set(PlayerState::Killed);
				m_state0.Set(PlayerState::Stunned);

				// ACT & ASSERT
				EXPECT_TRUE(m_state0.AreAllSet());
#pragma endregion

#pragma region
				m_state0.Set(PlayerState::Killed);

				// ACT & ASSERT
				EXPECT_TRUE(m_state0.AreAllSet());
#pragma endregion
			}

			/// Tests all operator|(...) overloads.
			TEST_F(FlagsTest, Bitwise_Or_Operator)
			{
#pragma region
				// ACT
				m_state0 = PlayerState::Floating | PlayerState::Dazed;

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				m_state0 = m_state0 | m_state1;

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				m_state0 = m_state1 | PlayerState::Killed;

				// ASSERT
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				m_state0 = PlayerState::Floating | m_state1;

				// ASSERT
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion
			}

			/// Tests all operator |=(...) overloads.
			TEST_F(FlagsTest, Bitwise_Or_Assignment_Operator)
			{
#pragma region
				// ACT
				// set and remove some flags - type-safe!
				m_state0 |= m_state1;

				// ASSERT
				//EXPECT_EQ(m_state0, m_state1);
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Floating));

				EXPECT_FALSE(m_state1.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state1.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				m_state0 |= PlayerState::Dazed;

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Floating));
#pragma endregion

#pragma region
				// ACT
				m_state0 |= m_state1 |= PlayerState::Killed;

				// ASSERT
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state0.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state0.IsSet(PlayerState::Floating));

				EXPECT_FALSE(m_state1.IsSet(PlayerState::Dazed));
				EXPECT_TRUE(m_state1.IsSet(PlayerState::Stunned));
				EXPECT_TRUE(m_state1.IsSet(PlayerState::Killed));
				EXPECT_FALSE(m_state1.IsSet(PlayerState::Floating));
#pragma endregion
			}

			/// Tests ToString(T::Description).
			TEST_F(FlagsTest, ToString)
			{
				// ACT & ASSERT
				PlayerFlags::Description desc = {};
				EXPECT_STREQ("", m_state0.ToString(desc));

				// ACT & ASSERT
				EXPECT_STREQ("Stunned", m_state1.ToString(desc));

#pragma region
				// ARRANGE
				m_state1.Set(PlayerState::Killed);
				m_state1.Set(PlayerState::Floating);

				// ACT
				desc[0] = 0;
				m_state1.ToString(desc);

				// ASSERT
				EXPECT_STREQ("Stunned, Killed, Floating", desc);
#pragma endregion

#pragma region
				// ARRANGE
				m_state1.Remove(PlayerState::Killed);

				// ACT
				desc[0] = 0;
				m_state1.ToString(desc);

				// ASSERT
				EXPECT_STREQ("Stunned, Floating", desc);
#pragma endregion

#pragma region
				// ARRANGE
				m_state1.Set(PlayerState::Dazed);

				// ACT
				desc[0] = 0;
				m_state1.ToString(desc);

				// ASSERT
				EXPECT_STREQ("Dazed, Stunned, Floating", desc);
#pragma endregion

#pragma region
				// ARRANGE
				m_state1.Remove(PlayerState::Floating);

				// ACT
				desc[0] = 0;
				m_state1.ToString(desc);

				// ASSERT
				EXPECT_STREQ("Dazed, Stunned", desc);
#pragma endregion

#pragma region
				// ARRANGE
				m_state1.Remove(PlayerState::Dazed);
				m_state1.Remove(PlayerState::Stunned);

				// ACT
				desc[0] = 0;
				m_state1.ToString(desc);

				// ASSERT
				EXPECT_STREQ("", desc);
#pragma endregion
			}
		}
	}
}
