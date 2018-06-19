#pragma once

#include <malius/preprocessor/facilities/expand.hpp>
#include <malius/preprocessor/facilities/glue.hpp>

#include <malius/preprocessor/control/iif.hpp>
#include <malius/preprocessor/detail/check.hpp>
//#include <malius/preprocessor/logical/not.hpp>

// TODO: detect if the actually is a paranthesis, see boost implementation below
#define  MA_PP_REMOVE_PARENS(x)  MA_PP_EXPAND x
#define  MA_PP_REMOVE_PARENS_GLUED(x)  MA_PP_GLUE( MA_PP_EXPAND, x)

#define  MA_PP_IS_PAREN_PROBE(...)  MA_PP_PROBE(~)
#define  MA_PP_IS_PAREN(x)  MA_PP_CHECK( MA_PP_IS_PAREN_PROBE x)
/* TESTS
// Expands to 1
 MA_PP_IS_PAREN((10,9,8,7,6,5,4,3,2,1))
;
// Expands to 0
 MA_PP_IS_PAREN(xxx)
;
 MA_PP_CHECK( MA_PP_IS_PAREN_PROBE(10, 9, 8, 7, 6, 5, 4, 3, 2, 1))
;
 MA_PP_CHECK( MA_PP_IS_PAREN_PROBE xxx)
;
*/

// 2 scans?
#define  MA_PP_REMOVE_PARENS_COND(param) \
     MA_PP_IIF                       \
    (                               \
         MA_PP_IS_PAREN(param),      \
             MA_PP_REMOVE_PARENS,    \
             MA_PP_EXPAND            \
            /* MA_PP_EXPAND_SINGLE // would need one additional expansion compared to  MA_PP_EXPAND because __VA_ARGS__ triggers additional expansion*/ \
    )                               \
    (param)

/* TESTS
 MA_PP_REMOVE_PARENS_COND((10, 9, 8, 7, 6, 5, 4, 3, 2, 1));
 MA_PP_REMOVE_PARENS_COND(10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
 MA_PP_REMOVE_PARENS_COND(10);
 MA_PP_REMOVE_PARENS_COND( MA_PP_BOOL(10));
 MA_PP_REMOVE_PARENS_COND( MA_PP_NOT(10));
*/

/* **************************************************************************
 *                                                                          *
 *     (C) Copyright Edward Diener 2014.
 *     Distributed under the Boost Software License, Version 1.0. (See
 *     accompanying file LICENSE_1_0.txt or copy at
 *     http://www.boost.org/LICENSE_1_0.txt)
 *                                                                          *
 ************************************************************************** */

/*
#include <malius/preprocessor/config/config.hpp>

#if  MA_PP_VARIADICS

#include <malius/preprocessor/control/iif.hpp>
#include <malius/preprocessor/facilities/expand.hpp>
#include <malius/preprocessor/punctuation/is_begin_parens.hpp>
#include <malius/preprocessor/tuple/enum.hpp>

#define  MA_PP_REMOVE_PARENS_DO(param) \
   MA_PP_EXPAND_SINGLE( MA_PP_TUPLE_ENUM(param))

#define  MA_PP_REMOVE_PARENS(param) \
     MA_PP_IIF \
      ( \
       MA_PP_IS_BEGIN_PARENS(param), \
       MA_PP_REMOVE_PARENS_DO, \
       MA_PP_EXPAND_SINGLE \
      ) \
    (param)()

#endif //  MA_PP_VARIADICS
*/
