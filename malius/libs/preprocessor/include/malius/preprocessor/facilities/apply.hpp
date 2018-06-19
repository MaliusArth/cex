#pragma once

#define  MA_PP_APPLY(x, y) x(y)

/* **************************************************************************
*                                                                          *
*     (C) Copyright Paul Mensonides 2002.                                  *
*     Distributed under the ME Software License, Version 1.0. (See      *
*     accompanying file LICENSE_1_0.txt or copy at                         *
*     http://www.ME.org/LICENSE_1_0.txt)                                *
*                                                                          *
************************************************************************** */

//#include <malius/preprocessor/config/config.hpp>
//#include <malius/preprocessor/control/expr_iif.hpp>
//#include <malius/preprocessor/detail/is_unary.hpp>
//#include <malius/preprocessor/tuple/rem.hpp>
//
///*  MA_PP_APPLY */
//
//# if  MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
//#    define  MA_PP_APPLY(x)  MA_PP_APPLY_I(x)
//#    define  MA_PP_APPLY_I(x)  MA_PP_EXPR_IIF( MA_PP_IS_UNARY(x),  MA_PP_TUPLE_REM_1 x)
//# elif  MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_BCC()
//#    define  MA_PP_APPLY(x)  MA_PP_APPLY_I(x)
//#    define  MA_PP_APPLY_I(x)  MA_PP_APPLY_ ## x
//#    define  MA_PP_APPLY_(x) x
//#    define  MA_PP_APPLY_ MA_PP_NIL
//# else
//#    define  MA_PP_APPLY(x)  MA_PP_EXPR_IIF( MA_PP_IS_UNARY(x),  MA_PP_TUPLE_REM_1 x)
//# endif
