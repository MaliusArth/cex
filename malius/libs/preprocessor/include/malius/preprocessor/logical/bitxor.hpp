#pragma once

#include <malius/preprocessor/config/config.hpp>

/*  MA_PP_BITXOR */

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
#   define  MA_PP_BITXOR(x, y)  MA_PP_BITXOR_I(x, y)
#else
#   define  MA_PP_BITXOR_OO(par)  MA_PP_BITXOR_I ## par
#   define  MA_PP_BITXOR(x, y)  MA_PP_BITXOR_OO((x, y))
#endif

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC()
#   define  MA_PP_BITXOR_I(x, y)  MA_PP_BITXOR_ ## x ## y
#else
#   define  MA_PP_BITXOR_ID(id) id   // TODO: replace w/  MA_PP_EXPAND_SINGLE(x) x
#   define  MA_PP_BITXOR_I(x, y)  MA_PP_BITXOR_ID( MA_PP_BITXOR_ ## x ## y)
#endif

#define  MA_PP_BITXOR_00 0
#define  MA_PP_BITXOR_01 1
#define  MA_PP_BITXOR_10 1
#define  MA_PP_BITXOR_11 0
