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

/*  MA_PP_BITOR */

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC()
#   define  MA_PP_BITOR_I(x, y)  MA_PP_BITOR_ ## x ## y
#else
#   define  MA_PP_BITOR_ID(id) id    // TODO: replace w/  MA_PP_EXPAND_SINGLE(x) x
#   define  MA_PP_BITOR_I(x, y)  MA_PP_BITOR_ID( MA_PP_BITOR_ ## x ## y)
#endif

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
#   define  MA_PP_BITOR(x, y)  MA_PP_BITOR_I(x, y)
#else
#   define  MA_PP_BITOR_OO(par)  MA_PP_BITOR_I ## par
#   define  MA_PP_BITOR(x, y)  MA_PP_BITOR_OO((x, y))
#endif

#define  MA_PP_BITOR_00 0
#define  MA_PP_BITOR_01 1
#define  MA_PP_BITOR_10 1
#define  MA_PP_BITOR_11 1
