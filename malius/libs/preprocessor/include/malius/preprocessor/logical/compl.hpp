#pragma once

#include <malius/preprocessor/cat.hpp>

// complement
#define  MA_PP_COMPL(boolean)  MA_PP_CAT_HELPER( MA_PP_COMPL_, boolean)
#define  MA_PP_COMPL_0 1
#define  MA_PP_COMPL_1 0

// MA_PP_COMPL(1);

/* **************************************************************************
 *                                                                          *
 *     (C) Copyright Paul Mensonides 2002.
 *     Distributed under the Boost Software License, Version 1.0. (See
 *     accompanying file LICENSE_1_0.txt or copy at
 *     http://www.boost.org/LICENSE_1_0.txt)
 *                                                                          *
 ************************************************************************** */

//#include <malius/preprocessor/config/config.hpp>
//#include <malius/preprocessor/facilities/expand.hpp>

//  MA_PP_COMPL

//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC()
//#   define  MA_PP_COMPL_I(x)  MA_PP_COMPL_ ## x
//#else
//#   define  MA_PP_COMPL_ID(id) id
//#   define  MA_PP_COMPL_I(x)  MA_PP_COMPL_ID( MA_PP_COMPL_ ## x)
////#   define  MA_PP_COMPL_I(x)  MA_PP_EXPAND_SINGLE( MA_PP_COMPL_ ## x)
////#   define  MA_PP_COMPL_I(x)  MA_PP_EXPAND( MA_PP_COMPL_ ## x)
////#   define  MA_PP_COMPL_I(x)  MA_PP_CAT_HELPER( MA_PP_COMPL_, x)
//#endif
//
//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
//#   define  MA_PP_COMPL(x)  MA_PP_COMPL_I(x)
//#else
//#   define  MA_PP_COMPL_OO(par)  MA_PP_COMPL_I ## par
//#   define  MA_PP_COMPL(x)  MA_PP_COMPL_OO((x))
//#endif
//
//#define  MA_PP_COMPL_0 1
//#define  MA_PP_COMPL_1 0

// MA_PP_COMPL(1);
