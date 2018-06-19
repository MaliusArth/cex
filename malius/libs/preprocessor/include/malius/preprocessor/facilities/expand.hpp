#pragma once

// Reference: http://stackoverflow.com/a/32400131/2190476
#define  MA_PP_EXPAND(...) __VA_ARGS__
#define  MA_PP_EXPAND_SINGLE(x) x


/* **************************************************************************
*                                                                          *
*     (C) Copyright Paul Mensonides 2002.                                  *
*     Distributed under the Boost Software License, Version 1.0. (See      *
*     accompanying file LICENSE_1_0.txt or copy at                         *
*     http://www.boost.org/LICENSE_1_0.txt)                                *
*                                                                          *
************************************************************************** */

//#include <malius/preprocessor/config/config.hpp>

//#define  MA_PP_EXPAND_I(x) x
//
//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC() && ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_DMC()
//#   define  MA_PP_EXPAND(x)  MA_PP_EXPAND_I(x)
//#else
//#   define  MA_PP_EXPAND_OO(par)  MA_PP_EXPAND_I ## par
//#   define  MA_PP_EXPAND(x)  MA_PP_EXPAND_OO((x))
//#endif
