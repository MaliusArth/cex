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

#include <malius/preprocessor/config/config.hpp>
#include <malius/preprocessor/logical/bool.hpp>
#include <malius/preprocessor/logical/bitnor.hpp>

/*  MA_PP_NOR */

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
#   define  MA_PP_NOR(p, q)  MA_PP_BITNOR( MA_PP_BOOL(p),  MA_PP_BOOL(q))
#else
#   define  MA_PP_NOR(p, q)  MA_PP_NOR_I(p, q)
#   define  MA_PP_NOR_I(p, q)  MA_PP_BITNOR( MA_PP_BOOL(p),  MA_PP_BOOL(q))
#endif