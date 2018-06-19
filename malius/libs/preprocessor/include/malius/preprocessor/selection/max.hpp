#pragma once

#include <algorithm>

#include <malius/preprocessor/facilities/expand.hpp>
#include <malius/preprocessor/facilities/overload.hpp>
#include <malius/preprocessor/facilities/glue.hpp>

// TODO: replace with compile time max if possible, see bottom boost implementation
#define  MA_PP_MAX_2(a, b)          ::std::max(a, b)
#define  MA_PP_MAX_3(a, b, c)        MA_PP_MAX_2( MA_PP_MAX_2(a, b), c)
#define  MA_PP_MAX_4(a, b, c, d)     MA_PP_MAX_2( MA_PP_MAX_3(a, b, c), d)

#define  MA_PP_MAX(...)      MA_PP_EXPAND( MA_PP_GLUE( MA_PP_OVERLOAD( MA_PP_MAX_, __VA_ARGS__), (__VA_ARGS__)))

// alternative without  MA_PP_GLUE
////#define  MA_PP_MAX(...)      MA_PP_EXPAND( MA_PP_OVERLOAD( MA_PP_MAX_, __VA_ARGS__)(__VA_ARGS__))



/*
#include <malius/preprocessor/comparison/less_equal.hpp>
#include <malius/preprocessor/config/config.hpp>
#include <malius/preprocessor/control/iif.hpp>

//  MA_PP_MAX

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
#   define  MA_PP_MAX(x, y)  MA_PP_IIF( MA_PP_LESS_EQUAL(x, y), y, x)
#else
#   define  MA_PP_MAX_I(x, y)  MA_PP_IIF( MA_PP_LESS_EQUAL(x, y), y, x)
#   define  MA_PP_MAX(x, y)  MA_PP_MAX_I(x, y)
#endif

//  MA_PP_MAX_D

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
#   define  MA_PP_MAX_D(d, x, y)  MA_PP_IIF( MA_PP_LESS_EQUAL_D(d, x, y), y, x)
#else
#   define  MA_PP_MAX_D_I(d, x, y)  MA_PP_IIF( MA_PP_LESS_EQUAL_D(d, x, y), y, x)
#   define  MA_PP_MAX_D(d, x, y)  MA_PP_MAX_D_I(d, x, y)
#endif
*/
