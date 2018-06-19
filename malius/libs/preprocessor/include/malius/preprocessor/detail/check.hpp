#pragma once

#define  MA_PP_CHECK_N(x, n, ...) n
#define  MA_PP_CHECK(...)  MA_PP_CHECK_N(__VA_ARGS__, 0)
#define  MA_PP_PROBE(x) x, 1

/* TODO: tests
// MA_PP_CHECK( MA_PP_PROBE(~)) // Expands to 1
;
// MA_PP_CHECK(xxx) // Expands to 0
;
*/

/*
#include <malius/preprocessor/cat.hpp>
#include <malius/preprocessor/config/config.hpp>

//  MA_PP_CHECK

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC() && ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_DMC()
#   define  MA_PP_CHECK_2(res, _) res
#   define  MA_PP_CHECK_1(chk)  MA_PP_CHECK_2(chk)
#   define  MA_PP_CHECK_D(x, type)  MA_PP_CHECK_1( MA_PP_CAT( MA_PP_CHECK_RESULT_, type x))
#elif  MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC()
#   define  MA_PP_CHECK_5(res) res
#   define  MA_PP_CHECK_4(res, _) res
#   define  MA_PP_CHECK_3(im)  MA_PP_CHECK_5( MA_PP_CHECK_4 im)
#   define  MA_PP_CHECK_2(chk)  MA_PP_CHECK_3(( MA_PP_CHECK_RESULT_ ## chk))
#   define  MA_PP_CHECK_1(chk)  MA_PP_CHECK_2(chk)
#   define  MA_PP_CHECK_D(x, type)  MA_PP_CHECK_1(type x)
#else // DMC
#   define  MA_PP_CHECK_2(res, _) res
#   define  MA_PP_CHECK_1(chk)  MA_PP_CHECK_2(chk)
#   define  MA_PP_CHECK_0(chk)  MA_PP_CHECK_1( MA_PP_CAT( MA_PP_CHECK_RESULT_, chk))
#   define  MA_PP_CHECK_OO(par)  MA_PP_CHECK_0 ## par
#   define  MA_PP_CHECK_D(x, type)  MA_PP_CHECK_OO((type x))
#endif

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
#   define  MA_PP_CHECK(x, type)  MA_PP_CHECK_D(x, type)
#else
#   define  MA_PP_CHECK_OO(par)  MA_PP_CHECK_D ## par
#   define  MA_PP_CHECK(x, type)  MA_PP_CHECK_OO((x, type))
#endif

// The  MA_PP_NIL identifier is reserved by the library to indicate a non-macro.
// Usage: BOOST_PP_NIL
// Remarks: 
// This identifier is not defined. Its purpose is to not be a macro.It is also used to terminate a list.
#define  MA_PP_CHECK_RESULT_1 1,  MA_PP_NIL
*/