///* Copyright (C) 2001
// * Housemarque Oy
// * http://www.housemarque.com
// *
// * Distributed under the Boost Software License, Version 1.0. (See
// * accompanying file LICENSE_1_0.txt or copy at
// * http://www.boost.org/LICENSE_1_0.txt)
// */
//
///* Revised by Paul Mensonides (2002) */
//
//#pragma once
//
//#include <malius/preprocessor/config/config.hpp>
//#include <malius/preprocessor/control/expr_iif.hpp>
//#include <malius/preprocessor/control/iif.hpp>
//#include <malius/preprocessor/logical/not.hpp>
//#include <malius/preprocessor/tuple/eat.hpp>
////#include <malius/preprocessor/facilities/eat.hpp>
//
////  MA_PP_ASSERT
//
//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
//#   define  MA_PP_ASSERT  MA_PP_ASSERT_D
//#else
//#   define  MA_PP_ASSERT(cond)  MA_PP_ASSERT_D(cond)
//#endif
//
//#define  MA_PP_ASSERT_D(cond)  MA_PP_IIF( MA_PP_NOT(cond),  MA_PP_ASSERT_ERROR,  MA_PP_TUPLE_EAT_1)(...)
//#define  MA_PP_ASSERT_ERROR(x, y, z)
//
///*  MA_PP_ASSERT_MSG */
//
//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
//#   define  MA_PP_ASSERT_MSG  MA_PP_ASSERT_MSG_D
//#else
//#   define  MA_PP_ASSERT_MSG(cond, msg)  MA_PP_ASSERT_MSG_D(cond, msg)
//#endif
//
//#define  MA_PP_ASSERT_MSG_D(cond, msg)  MA_PP_EXPR_IIF( MA_PP_NOT(cond), msg)
