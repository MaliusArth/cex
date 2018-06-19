#pragma once

#include <malius/preprocessor/detail/check.hpp>
#include <malius/preprocessor/cat.hpp>

//// expands everything but 0 to 1 (true) including  MA_PP_NIL or  MA_PP_NOT_PROPERLY_EXPANDED
#define  MA_PP_NOT_ANY(x)  MA_PP_CHECK( MA_PP_CAT_HELPER( MA_PP_NOT_ANY_, x))
#define  MA_PP_NOT_ANY_0  MA_PP_PROBE(~)

/*
// TESTS
 MA_PP_NOT_ANY(0);
 MA_PP_NOT_ANY(1);
 MA_PP_NOT_ANY(7);
 MA_PP_NOT_ANY(anything);
*/