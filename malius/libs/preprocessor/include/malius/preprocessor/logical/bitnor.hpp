/* **************************************************************************
 *                                                                          *
 *     (C) Copyright Paul Mensonides 2002.
 *     Distributed under the Boost Software License, Version 1.0. (See
 *     accompanying file LICENSE_1_0.txt or copy at
 *     http://www.boost.org/LICENSE_1_0.txt)
 *                                                                          *
 ************************************************************************** */

#pragma once

#include <malius/preprocessor/config/config.hpp>

/*  MA_PP_BITNOR */

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC()
#   define  MA_PP_BITNOR_I(x, y)  MA_PP_BITNOR_ ## x ## y
#else
#   define  MA_PP_BITNOR_ID(id) id   // TODO: replace w/  MA_PP_EXPAND_SINGLE(x) x
#   define  MA_PP_BITNOR_I(x, y)  MA_PP_BITNOR_ID( MA_PP_BITNOR_ ## x ## y)
#endif

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
#   define  MA_PP_BITNOR(x, y)  MA_PP_BITNOR_I(x, y)
#else
#   define  MA_PP_BITNOR_OO(par)  MA_PP_BITNOR_I ## par
#   define  MA_PP_BITNOR(x, y)  MA_PP_BITNOR_OO((x, y))
#endif

#define  MA_PP_BITNOR_00 1
#define  MA_PP_BITNOR_01 0
#define  MA_PP_BITNOR_10 0
#define  MA_PP_BITNOR_11 0
