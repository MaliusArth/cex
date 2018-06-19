#pragma once

//#include <malius/preprocessor.hpp>
#include <malius/preprocessor/dec.hpp>

//#include <malius/preprocessor/config/config.hpp>
#include <malius/preprocessor/detail/check.hpp>

int qwert =  MA_PP_DEC(6);


#include <malius/preprocessor/logical/not.hpp>
#include <malius/preprocessor/cat.hpp>

//#define  MA_PP_CHECK_N(x, n, ...) n
//#define  MA_PP_CHECK(...)  MA_PP_CHECK_N(__VA_ARGS__, 1)
//#define  MA_PP_IS_TRUE_PROBE() "ignored", 0
//
//#define  MA_PP_IS_TRUE(x)  MA_PP_CHECK( MA_PP_CAT_NX( MA_PP_IS_TRUE_, x))
//#define  MA_PP_IS_TRUE_0  MA_PP_IS_TRUE_PROBE(~)
//
#define  MA_PP_LOL
//
// MA_PP_IS_TRUE(7)
//
// MA_PP_IS_TRUE(0)
//
// MA_PP_IS_TRUE( MA_PP_NIL)
//
// MA_PP_IS_TRUE( MA_PP_LOL)

#include <malius/preprocessor/logical/bool.hpp>

 MA_PP_BOOL(7)
1

 MA_PP_BOOL(0)
0

 MA_PP_BOOL( MA_PP_NIL)
 MA_PP_BOOL_ MA_PP_NIL

 MA_PP_BOOL( MA_PP_LOL)
 MA_PP_BOOL_







 MA_PP_NOT(7)

 MA_PP_NOT(0)

 MA_PP_NOT( MA_PP_NIL)

 MA_PP_NOT( MA_PP_LOL)




//#define  MA_PP_BOOL(x)  MA_PP_COMPL( MA_PP_NOT(x))

 MA_PP_BOOL(7)
 MA_PP_BOOL(7)

 MA_PP_BOOL(1)
 MA_PP_BOOL(1)

 MA_PP_BOOL(0)
 MA_PP_BOOL(0)

 MA_PP_BOOL( MA_PP_NIL)
 MA_PP_BOOL( MA_PP_NIL)

 MA_PP_BOOL( MA_PP_LOL)
 MA_PP_BOOL( MA_PP_LOL)

#include <malius/preprocessor/variadic/size.hpp>

 MA_PP_VARIADIC_SIZE(q,w,e,r,t,z,u)



