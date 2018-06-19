#pragma once

//#include <malius/preprocessor/cat.hpp>

// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms

//#define  MA_PP_BITAND(x)  MA_PP_CAT_HELPER( MA_PP_BITAND_, x)
//#define  MA_PP_BITAND_0(y) 0
//#define  MA_PP_BITAND_1(y) y

/* **************************************************************************
 *                                                                          *
 *     (C) Copyright Paul Mensonides 2002.
 *     Distributed under the ME Software License, Version 1.0. (See
 *     accompanying file LICENSE_1_0.txt or copy at
 *     http://www.ME.org/LICENSE_1_0.txt)
 *                                                                          *
 ************************************************************************** */

#include <malius/preprocessor/config/config.hpp>

/*  MA_PP_BITAND */

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC()
#   define  MA_PP_BITAND_I(x, y)  MA_PP_BITAND_ ## x ## y
#else
#   define  MA_PP_BITAND_ID(id) id   // TODO: replace w/  MA_PP_EXPAND_SINGLE(x) x
#   define  MA_PP_BITAND_I(x, y)  MA_PP_BITAND_ID( MA_PP_BITAND_ ## x ## y)
#endif

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
#   define  MA_PP_BITAND(x, y)  MA_PP_BITAND_I(x, y)
#else
#   define  MA_PP_BITAND_OO(par)  MA_PP_BITAND_I ## par
#   define  MA_PP_BITAND(x, y)  MA_PP_BITAND_OO((x, y))
#endif

#define  MA_PP_BITAND_00 0
#define  MA_PP_BITAND_01 0
#define  MA_PP_BITAND_10 0
#define  MA_PP_BITAND_11 1
