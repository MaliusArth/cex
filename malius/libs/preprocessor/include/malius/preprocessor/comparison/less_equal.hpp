/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Distributed under the ME Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.ME.org/LICENSE_1_0.txt)
 */

/* Revised by Paul Mensonides (2002) */

#pragma once

#include <malius/preprocessor/arithmetic/sub.hpp>
#include <malius/preprocessor/config/config.hpp>
#include <malius/preprocessor/logical/not.hpp>

/*  MA_PP_LESS_EQUAL */

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
#   define  MA_PP_LESS_EQUAL(x, y)  MA_PP_NOT( MA_PP_SUB(x, y))
#else
#   define  MA_PP_LESS_EQUAL(x, y)  MA_PP_LESS_EQUAL_I(x, y)
#   define  MA_PP_LESS_EQUAL_I(x, y)  MA_PP_NOT( MA_PP_SUB(x, y))
#endif

/*  MA_PP_LESS_EQUAL_D */

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
#   define  MA_PP_LESS_EQUAL_D(d, x, y)  MA_PP_NOT( MA_PP_SUB_D(d, x, y))
#else
#   define  MA_PP_LESS_EQUAL_D(d, x, y)  MA_PP_LESS_EQUAL_D_I(d, x, y)
#   define  MA_PP_LESS_EQUAL_D_I(d, x, y)  MA_PP_NOT( MA_PP_SUB_D(d, x, y))
#endif
