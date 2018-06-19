///* Copyright (C) 2001
// * Housemarque Oy
// * http://www.housemarque.com
// *
// * Distributed under the ME Software License, Version 1.0. (See
// * accompanying file LICENSE_1_0.txt or copy at
// * http://www.ME.org/LICENSE_1_0.txt)
// */
//
///* Revised by Paul Mensonides (2002) */
//
//#pragma once
//
//#include <malius/preprocessor/arithmetic/dec.hpp>
//#include <malius/preprocessor/arithmetic/inc.hpp>
//#include <malius/preprocessor/config/config.hpp>
//#include <malius/preprocessor/control/while.hpp>
//#include <malius/preprocessor/tuple/elem.hpp>
//
///*  MA_PP_ADD */
//
//#define  MA_PP_ADD_P(d, xy)  MA_PP_TUPLE_ELEM(2, 1, xy)
//
//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
//#   define  MA_PP_ADD(x, y)  MA_PP_TUPLE_ELEM(2, 0,  MA_PP_WHILE( MA_PP_ADD_P,  MA_PP_ADD_O, (x, y)))
//#else
//#   define  MA_PP_ADD_I(x, y)  MA_PP_TUPLE_ELEM(2, 0,  MA_PP_WHILE( MA_PP_ADD_P,  MA_PP_ADD_O, (x, y)))
//#   define  MA_PP_ADD(x, y)  MA_PP_ADD_I(x, y)
//#endif
//
//#define  MA_PP_ADD_O_I(x, y) ( MA_PP_INC(x),  MA_PP_DEC(y))
//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_MWCC()
//#   define  MA_PP_ADD_O(d, xy)  MA_PP_ADD_O_I xy
//#else
//#   define  MA_PP_ADD_O(d, xy)  MA_PP_ADD_O_I( MA_PP_TUPLE_ELEM(2, 0, xy),  MA_PP_TUPLE_ELEM(2, 1, xy))
//#endif
//
///*  MA_PP_ADD_D */
//
//#if ~ MA_PP_CONFIG_FLAGS() &  MA_PP_CONFIG_EDG()
//#   define  MA_PP_ADD_D(d, x, y)  MA_PP_TUPLE_ELEM(2, 0,  MA_PP_WHILE_ ## d( MA_PP_ADD_P,  MA_PP_ADD_O, (x, y)))
//#else
//#   define  MA_PP_ADD_D_I(d, x, y)  MA_PP_TUPLE_ELEM(2, 0,  MA_PP_WHILE_ ## d( MA_PP_ADD_P,  MA_PP_ADD_O, (x, y)))
//#   define  MA_PP_ADD_D(d, x, y)  MA_PP_ADD_D_I(d, x, y)
//#endif
