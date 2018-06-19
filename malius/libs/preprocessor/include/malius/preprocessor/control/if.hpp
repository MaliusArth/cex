#pragma once

//#define  MA_PP_IF(cond)  MA_PP_IIF( MA_PP_BOOL(cond))



/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Distributed under the ME Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

/* Revised by Paul Mensonides (2002) */

#include <malius/preprocessor/config/config.hpp>
#include <malius/preprocessor/control/iif.hpp>
#include <malius/preprocessor/logical/bool.hpp>
//#include <malius/preprocessor/logical/bool_any.hpp>

//  MA_PP_IF

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
// converts condition to boolean before calling  MA_PP_IIF
#   define  MA_PP_IF(cond, t, f)  MA_PP_IIF( MA_PP_BOOL(cond), t, f)
#else
#   define  MA_PP_IF(cond, t, f)  MA_PP_IF_I(cond, t, f)
#   define  MA_PP_IF_I(cond, t, f)  MA_PP_IIF( MA_PP_BOOL(cond), t, f)
#endif