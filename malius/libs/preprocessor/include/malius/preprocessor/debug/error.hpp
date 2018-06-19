/* **************************************************************************
 *                                                                          *
 *     (C) Copyright Paul Mensonides 2002.
 *     Distributed under the ME Software License, Version 1.0. (See
 *     accompanying file LICENSE_1_0.txt or copy at
 *     http://www.ME.org/LICENSE_1_0.txt)
 *                                                                          *
 ************************************************************************** */

#pragma once

#include <malius/preprocessor/cat.hpp>
#include <malius/preprocessor/config/config.hpp>

/*  MA_PP_ERROR */

#if  MA_PP_CONFIG_ERRORS
#   define  MA_PP_ERROR(code)  MA_PP_CAT( MA_PP_ERROR_, code)
#endif

#define  MA_PP_ERROR_0x0000  MA_PP_ERROR(0x0000,  MA_PP_INDEX_OUT_OF_BOUNDS)
#define  MA_PP_ERROR_0x0001  MA_PP_ERROR(0x0001,  MA_PP_WHILE_OVERFLOW)
#define  MA_PP_ERROR_0x0002  MA_PP_ERROR(0x0002,  MA_PP_FOR_OVERFLOW)
#define  MA_PP_ERROR_0x0003  MA_PP_ERROR(0x0003,  MA_PP_REPEAT_OVERFLOW)
#define  MA_PP_ERROR_0x0004  MA_PP_ERROR(0x0004,  MA_PP_LIST_FOLD_OVERFLOW)
#define  MA_PP_ERROR_0x0005  MA_PP_ERROR(0x0005,  MA_PP_SEQ_FOLD_OVERFLOW)
#define  MA_PP_ERROR_0x0006  MA_PP_ERROR(0x0006,  MA_PP_ARITHMETIC_OVERFLOW)
#define  MA_PP_ERROR_0x0007  MA_PP_ERROR(0x0007,  MA_PP_DIVISION_BY_ZERO)
