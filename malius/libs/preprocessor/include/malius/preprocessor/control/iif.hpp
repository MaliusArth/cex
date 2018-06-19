#pragma once

//#include <malius/preprocessor/cat.hpp>

// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms

//#define  MA_PP_IIF_0(t, f) f
//#define  MA_PP_IIF_1(t, f) t
// 3 scans
//#define  MA_PP_IIF(bit)  MA_PP_CAT_HELPER( MA_PP_IIF_, bit)

// usage:
// MA_PP_IIF(0)(trueResult, falseResult)

/* **************************************************************************
 *                                                                          *
 *     (C) Copyright Paul Mensonides 2002.
 *     Distributed under the Boost Software License, Version 1.0. (See
 *     accompanying file LICENSE_1_0.txt or copy at
 *     http://www.boost.org/LICENSE_1_0.txt)
 *                                                                          *
 ************************************************************************** */
/**/
#include <malius/preprocessor/config/config.hpp>
//#include <malius/preprocessor/cat.hpp>
#include <malius/preprocessor/facilities/expand.hpp>

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MSVC()
#   define  MA_PP_IIF_I(bit, t, f)  MA_PP_IIF_ ## bit(t, f)
#else
// 3 scans or 1 scan?
//#   define  MA_PP_IIF_II(id) id  // TODO: =  MA_PP_EXPAND_SINGLE(x)
//#   define  MA_PP_IIF_I(bit, t, f)  MA_PP_IIF_II( MA_PP_IIF_ ## bit(t, f))
#   define  MA_PP_IIF_I(bit, t, f)  MA_PP_EXPAND_SINGLE( MA_PP_IIF_ ## bit(t, f))
//#   define  MA_PP_IIF_I(bit, t, f)  MA_PP_IIF_ ## bit(t, f)
// 4 scans or 1 scan?
//#   define  MA_PP_IIF_I(bit, t, f)  MA_PP_CAT_HELPER( MA_PP_IIF_, bit(t, f))
#endif

#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
#   define  MA_PP_IIF(bit, t, f)  MA_PP_IIF_I(bit, t, f)
#else
#   define  MA_PP_IIF_OO(par)  MA_PP_IIF_I ## par
#   define  MA_PP_IIF(bit, t, f)  MA_PP_IIF_OO((bit, t, f))
#endif

#define  MA_PP_IIF_0(t, f) f
#define  MA_PP_IIF_1(t, f) t

// usage
// MA_PP_IIF(0, trueResult, falseResult)
