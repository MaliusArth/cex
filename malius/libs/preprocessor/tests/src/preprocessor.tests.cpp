// external libraries
#include <gtest/gtest.h>

// tested libraries
//#include <malius/core/breakpoint.hpp>
//#include <malius/Preprocessor.hpp>
#include <malius/preprocessor/selection/max.hpp>
#include <malius/preprocessor/logical/compl.hpp>
#include <malius/preprocessor/stringize.hpp>
//#include "malius/preprocessor/logical/bool_any.hpp"

namespace ma
{
    namespace test
    {
        namespace preprocessor
        {
            //TEST(test, test)
            //{
            //    EXPECT_EQ(1, 2 - 1);
            //}

            // Tests the usage of the MA_BREAKPOINT macro
            //TEST(Breakpoint, Preprocessor)
            //{
            //    const std::string test("Breakpoint test");
            //    MA_BREAKPOINT;  //  test should be aborted here
            //    EXPECT_TRUE(true);
            //}

            TEST(MA_PP_COMPL, logical)
            {
                EXPECT_EQ(MA_PP_COMPL(0), 1);
                EXPECT_EQ(MA_PP_COMPL(1), 0);
                EXPECT_STRNE(MA_PP_STRINGIZE(MA_PP_COMPL(7)), MA_PP_STRINGIZE(0));
                EXPECT_STREQ(MA_PP_STRINGIZE(MA_PP_COMPL(7)), "MA_PP_COMPL_7");
                EXPECT_STREQ(MA_PP_STRINGIZE(MA_PP_COMPL(not_supported)), "MA_PP_COMPL_not_supported");
                EXPECT_STREQ(MA_PP_STRINGIZE(MA_PP_COMPL("wtf")), "MA_PP_COMPL_\"wtf\"");
            }

            TEST(MA_PP_MAX, selection)
            {
                EXPECT_EQ(7, MA_PP_MAX(2, 7, 6, 5));
            }
        }
    }
}
