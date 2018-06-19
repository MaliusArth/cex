#pragma once

// external libraries
#include <gtest/gtest.h>

// tested libraries
#include "containers/Flags.hpp"

namespace ma
{
	namespace test
	{
		namespace flags
		{

#define  MA_PP_TEST_ENUM(name, ...)\
	enum name\
	{\
		 MA_PP_FOR_EACH_ITER_TEST( MA_DECLARE_FLAGS_ENUM, __VA_ARGS__)\
	}

			// MA_PP_TEST_ENUM(PlayerState1, Dazed, Stunned);

			// TODO: c++11 macro for each & remove parens

			// MA_DECLARE_FLAGS(PlayerState, (Dazed), (Stunned), (Killed), (Floating));

			// MA_DECLARE_FLAGS(PlayerState, Dazed, Stunned, Killed, Floating);

			 MA_DECLARE_FLAGS(PlayerState, Dazed, Stunned, Killed, Floating);

			typedef Flags<PlayerState> PlayerFlags;

			class FlagsTest : public ::testing::Test
			{
			protected:  // You should make the members protected so that they can be
						// accessed from sub-classes.

				// virtual void SetUp() will be called before each test is run. You
				// should define it if you need to initialize the varaibles.
				// Otherwise, this can be skipped.
				virtual void SetUp(void)  MA_OVERRIDE
				{
					// ARRANGE
					m_state1 = PlayerFlags(PlayerState::Stunned);

#ifdef  MA_INIT_LISTS
					m_state2 = PlayerFlags{ PlayerState::Stunned, PlayerState::Floating };
#endif //  MA_INIT_LISTS

				}

				// virtual void TearDown() will be called after each test is run.
				// You should define it if there is cleanup work to do.  Otherwise,
				// you don't have to provide it.
				//
				// virtual void TearDown()
				// {
				// }

				// Declares the variables your tests want to use.
				PlayerFlags m_state0;
				PlayerFlags m_state1;
				PlayerFlags m_state2;
			};
		}
	}
}
