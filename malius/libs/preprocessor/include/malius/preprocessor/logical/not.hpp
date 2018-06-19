#pragma once

/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/* Revised by Paul Mensonides (2002) */

#include <malius/preprocessor/config/config.hpp>
#include <malius/preprocessor/logical/compl.hpp>
#include <malius/preprocessor/logical/bool.hpp>

//  MA_PP_NOT

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
#   define  MA_PP_NOT(x)  MA_PP_COMPL( MA_PP_BOOL(x))
#else
#   define  MA_PP_NOT(x)  MA_PP_NOT_I(x)
#   define  MA_PP_NOT_I(x)  MA_PP_COMPL( MA_PP_BOOL(x))
#endif
