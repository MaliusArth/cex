// external libraries
#include <gtest/gtest.h>

// tested libraries
//#include <malius/log/Debug.hpp>
#include <malius/preprocessor.hpp>

namespace ma
{
    namespace test
    {
        namespace preprocessor
        {
            // Tests the usage of the MA_BREAKPOINT macro
            TEST(Breakpoint, Preprocessor)
            {
                const std::string test("Breakpoint test");
                //MA_BREAKPOINT;  //  test should be aborted here
                EXPECT_TRUE(true);
            }

            TEST(MA_MAX, Preprocessor)
            {
                EXPECT_EQ(7, MA_MAX(2, 7, 6, 5));
            }
        }
    }
}
