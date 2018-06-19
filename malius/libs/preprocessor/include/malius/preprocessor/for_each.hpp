#pragma once

#include <malius/preprocessor/facilities/expand.hpp>
#include <malius/preprocessor/facilities/glue.hpp>
#include <malius/preprocessor/facilities/overload.hpp>


#pragma region MA_PP_FOR_EACH_SIMPLE_ITER range

#define MA_PP_FOR_EACH_SIMPLE_0(op, ...)
#define MA_PP_FOR_EACH_SIMPLE_1(op, a1)\
    op(a1)
#define MA_PP_FOR_EACH_SIMPLE_2(op, a1, a2)\
    op(a1) op(a2)
#define MA_PP_FOR_EACH_SIMPLE_3(op, a1, a2, a3)\
    op(a1) op(a2) op(a3)
#define MA_PP_FOR_EACH_SIMPLE_4(op, a1, a2, a3, a4)\
    op(a1) op(a2) op(a3) op(a4)
#define MA_PP_FOR_EACH_SIMPLE_5(op, a1, a2, a3, a4, a5)\
    op(a1) op(a2) op(a3) op(a4) op(a5)
#define MA_PP_FOR_EACH_SIMPLE_6(op, a1, a2, a3, a4, a5, a6)\
    op(a1) op(a2) op(a3) op(a4) op(a5) op(a6)
#define MA_PP_FOR_EACH_SIMPLE_7(op, a1, a2, a3, a4, a5, a6, a7)\
    op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7)
#define MA_PP_FOR_EACH_SIMPLE_8(op, a1, a2, a3, a4, a5, a6, a7, a8)\
    op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7) op(a8)
#define MA_PP_FOR_EACH_SIMPLE_9(op, a1, a2, a3, a4, a5, a6, a7, a8, a9)\
    op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7) op(a8) op(a9)
#define MA_PP_FOR_EACH_SIMPLE_10(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)\
    op(a1) op(a2) op(a3) op(a4) op(a5) op(a6) op(a7) op(a8) op(a9) op(a10)

#pragma endregion MA_PP_FOR_EACH_SIMPLE range

#define MA_PP_FOR_EACH_SIMPLE(op, ...) \
MA_PP_EXPAND(\
    MA_PP_GLUE(\
        MA_PP_OVERLOAD(MA_PP_FOR_EACH_SIMPLE_, __VA_ARGS__),\
        (op, __VA_ARGS__)\
    )\
)

//#define MA_PP_PASS_VA(...) MA_PP_OPEN_PAREN __VA_ARGS__ MA_PP_CLOSE_PAREN
//
//#define MA_PP_FOR_EACH_SIMPLE(op, ...) \
//MA_PP_EXPAND(\
//    /*MA_PP_GLUE(*/\
//        MA_PP_OVERLOAD(MA_PP_FOR_EACH_SIMPLE_, __VA_ARGS__)\
///*,*/\
//        MA_PP_PASS_VA(op, ##__VA_ARGS__)\
//    /*)*/\
//)

#pragma region MA_PP_FOR_EACH_SIMPLE_ITER range

#define MA_PP_FOR_EACH_SIMPLE_ITER_0(op, ...)
#define MA_PP_FOR_EACH_SIMPLE_ITER_1(op, a1)\
    op(0, a1)
#define MA_PP_FOR_EACH_SIMPLE_ITER_2(op, a1, a2)\
    op(0, a1) op(1, a2)
#define MA_PP_FOR_EACH_SIMPLE_ITER_3(op, a1, a2, a3)\
    op(0, a1) op(1, a2) op(2, a3)
#define MA_PP_FOR_EACH_SIMPLE_ITER_4(op, a1, a2, a3, a4)\
    op(0, a1) op(1, a2) op(2, a3) op(3, a4)
#define MA_PP_FOR_EACH_SIMPLE_ITER_5(op, a1, a2, a3, a4, a5)\
    op(0, a1) op(1, a2) op(2, a3) op(3, a4) op(4, a5)
#define MA_PP_FOR_EACH_SIMPLE_ITER_6(op, a1, a2, a3, a4, a5, a6)\
    op(0, a1) op(1, a2) op(2, a3) op(3, a4) op(4, a5) op(5, a6)
#define MA_PP_FOR_EACH_SIMPLE_ITER_7(op, a1, a2, a3, a4, a5, a6, a7)\
    op(0, a1) op(1, a2) op(2, a3) op(3, a4) op(4, a5) op(5, a6) op(6, a7)
#define MA_PP_FOR_EACH_SIMPLE_ITER_8(op, a1, a2, a3, a4, a5, a6, a7, a8)\
    op(0, a1) op(1, a2) op(2, a3) op(3, a4) op(4, a5) op(5, a6) op(6, a7) op(7, a8)
#define MA_PP_FOR_EACH_SIMPLE_ITER_9(op, a1, a2, a3, a4, a5, a6, a7, a8, a9)\
    op(0, a1) op(1, a2) op(2, a3) op(3, a4) op(4, a5) op(5, a6) op(6, a7) op(7, a8) op(8, a9)
#define MA_PP_FOR_EACH_SIMPLE_ITER_10(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)\
    op(0, a1) op(1, a2) op(2, a3) op(3, a4) op(4, a5) op(5, a6) op(6, a7) op(7, a8) op(8, a9) op(9, a10)

#pragma endregion MA_PP_FOR_EACH_SIMPLE_ITER range

#define MA_PP_FOR_EACH_SIMPLE_ITER(op, ...) \
MA_PP_EXPAND(\
    MA_PP_GLUE(\
        MA_PP_OVERLOAD(MA_PP_FOR_EACH_SIMPLE_ITER_, __VA_ARGS__),\
        (op, __VA_ARGS__)\
    )\
)


#include <malius/preprocessor/control/if.hpp>
#include <malius/preprocessor/punctuation/remove_parens.hpp>
#include <malius/preprocessor/arithmetic/inc.hpp>



// MA_PP_PASS_VA_ARGS passes __VA_ARGS__ as multiple parameters to another macro, working around the above-mentioned bug
//#if _MSC_VER >= 1400 /*&& _MSC_VER < 1900*/
//#   define MA_PP_PASS_VA_ARGS(...) \
//    MA_PP_EXPAND(__VA_ARGS__)
//#else
//#   define MA_PP_PASS_VA_ARGS(...) __VA_ARGS__
//#endif



///////////////////////////////////////////////////////
// TODO: test these
//#define MA_PP_GET_ARGS(f,args,...) args
//#define MA_PP_FOR_EACH_1(op, count, x, ...) \
//MA_PP_IF(MA_PP_EQUAL(MA_PP_COUNT_ARGS(MA_PP_REMOVE_PARENS(x)), 2)\
//(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), MA_PP_GET_ARGS(MA_PP_REMOVE_PARENS(x)))),\
//MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count)))\
//MA_PP_EAT(__VA_ARGS__)



//#define _MA_PP_FOR_EACH_0(op, count, x, ...) /*\
//    MA_PP_EAT(__VA_ARGS__)*/
//#define _MA_PP_FOR_EACH_1(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count)) /*\
//    MA_PP_EAT(__VA_ARGS__)*/
//#define _MA_PP_FOR_EACH_2(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count)) \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_1(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_3(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count)) \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_2(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_4(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count))  \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_3(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_5(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count))  \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_4(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_6(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count))  \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_5(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_7(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count))  \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_6(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_8(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count))  \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_7(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_9(op, count, x, ...) \
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count))  \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_8(op, MA_PP_INC(count), __VA_ARGS__))
//#define _MA_PP_FOR_EACH_10(op, count, x, ...)\
//    MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x), count))  \
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_9(op, MA_PP_INC(count), __VA_ARGS__))
//
//#define MA_PP_FOR_EACH(op, ...)\
//MA_PP_EXPAND(\
//    MA_PP_GLUE(\
//        MA_PP_OVERLOAD(_MA_PP_FOR_EACH_, __VA_ARGS__),\
//        (op, 0, __VA_ARGS__)\
//    )\
//)
//#define MA_PP_FOR_EACH(op, ...)\
//MA_PP_EXPAND(\
//    MA_PP_OVERLOAD(_MA_PP_FOR_EACH_, __VA_ARGS__)\
//    (op, 0, __VA_ARGS__)\
//)



//#define _MA_PP_FOR_EACH_0(op, count, x, ...)
//#define _MA_PP_FOR_EACH_1(op, count, x, ...)\
//    MA_PP_IF(MA_PP_IS_PAREN(x))             \
//    (                                       \
//        op(MA_PP_REMOVE_PARENS(x), count)    \
//    ,                                       \
//        op(x, count)                        \
//    )
//#define _MA_PP_FOR_EACH_2(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_1(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_3(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_2(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_4(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_3(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_5(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_4(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_6(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_5(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_7(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_6(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_8(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_7(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_9(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_8(op, MA_PP_INC(count), __VA_ARGS__)
//#define _MA_PP_FOR_EACH_10(op, count, x, ...)    \
//    _MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _MA_PP_FOR_EACH_9(op, MA_PP_INC(count), __VA_ARGS__)
//
//#define MA_PP_FOR_EACH(op, ...)\
//MA_PP_EXPAND(\
//    MA_PP_GLUE(\
//        MA_PP_OVERLOAD(_MA_PP_FOR_EACH_, __VA_ARGS__),\
//        (op, 0, __VA_ARGS__)\
//    )\
//)


#pragma region /*for each with separate if syntax MA_PP_IF(cond) (t, f)*/

//// TODO: MA_PP_FOR_EACH (w/o iterater)
//#define _MA_PP_FOR_EACH_0(op, ...)
//#define _MA_PP_FOR_EACH_1(op, x, ...)\
//    MA_PP_IF(MA_PP_IS_PAREN(x))             \
//    (                                       \
///*MA_PP_DEFER(op) needed due to "count" potentially not properly handled by "op" eg: MA_PP_EXPAND which returns all arguments including count*/\
//        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x)))    \
//    ,                                       \
//        MA_PP_GLUE(op, (x))                        \
//    )
//#define _MA_PP_FOR_EACH_2(op, x, ...)\
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_1(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_3(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_2(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_4(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_3(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_5(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_4(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_6(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_5(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_7(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_6(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_8(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_7(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_9(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_8(op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_10(op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_9(op, __VA_ARGS__))
//
//#define MA_PP_FOR_EACH(op, ...)\
//MA_PP_EXPAND(\
//    MA_PP_GLUE(\
//        MA_PP_OVERLOAD(_MA_PP_FOR_EACH_, __VA_ARGS__),\
//        (op, __VA_ARGS__)\
//    )\
//)
//
//
//
//
//// TODO: MA_PP_FOR_EACH_ITER (passes the iterater to op as first argument)
//#define _MA_PP_FOR_EACH_ITER_0(count, op, x, ...)
//#define _MA_PP_FOR_EACH_ITER_1(count, op, x, ...)\
//    MA_PP_IF(MA_PP_IS_PAREN(x))             \
//    (                                       \
//        MA_PP_GLUE(MA_PP_DEFER(op), /*MA_PP_DEFER(op) needed due to "count" potentially not properly handled by "op" eg: MA_PP_EXPAND which returns all arguments including count*/(count, MA_PP_REMOVE_PARENS(x)))    \
//    ,                                       \
//        MA_PP_GLUE(MA_PP_DEFER(op), (count, x))                        \
//    )
//#define _MA_PP_FOR_EACH_ITER_2(count, op, x, ...)\
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        , \
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_1(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_3(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_2(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_4(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_3(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_5(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_4(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_6(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_5(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_7(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_6(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_8(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_7(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_9(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_8(MA_PP_INC(count), op, __VA_ARGS__))
//#define _MA_PP_FOR_EACH_ITER_10(count, op, x, ...)    \
//    MA_PP_IF(MA_PP_IS_PAREN(x))\
//    (\
//        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x)))\
//        ,\
//        MA_PP_GLUE(op, (count, x))\
//    )\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_9(MA_PP_INC(count), op, __VA_ARGS__))
//
//#define MA_PP_FOR_EACH_ITER(op, ...)\
///*MA_PP_EXPAND(*/\
//    MA_PP_GLUE(\
//        MA_PP_OVERLOAD(_MA_PP_FOR_EACH_ITER_, __VA_ARGS__),\
//        (0, op, __VA_ARGS__)\
//    /*)*/\
//)

#pragma endregion /*for each with separate if syntax MA_PP_IF(cond) (t, f)*/


#pragma region /*for each with single if syntax MA_PP_IF(cond, t, f)*/

// TODO: MA_PP_FOR_EACH (w/o iterater)
#define _MA_PP_FOR_EACH_0(op, ...)
#define _MA_PP_FOR_EACH_1(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
/*MA_PP_DEFER(op) needed due to "count" potentially not properly handled by "op" eg: MA_PP_EXPAND which returns all arguments including count*/\
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )
#define _MA_PP_FOR_EACH_2(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_1(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_3(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_2(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_4(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_3(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_5(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_4(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_6(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_5(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_7(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_6(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_8(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_7(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_9(op, x, ...)               \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_8(op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_10(op, x, ...)              \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))),   \
        MA_PP_GLUE(op, (x))                         \
    )                                               \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_9(op, __VA_ARGS__))

#define MA_PP_FOR_EACH(op, ...)                             \
    MA_PP_EXPAND(                                           \
        MA_PP_GLUE(                                         \
            MA_PP_OVERLOAD(_MA_PP_FOR_EACH_, __VA_ARGS__),  \
            (op, __VA_ARGS__)                               \
        )                                                   \
    )




// TODO: MA_PP_FOR_EACH_ITER (passes the iterater to op as first argument)
#define _MA_PP_FOR_EACH_ITER_0(count, op, x, ...)
#define _MA_PP_FOR_EACH_ITER_1(count, op, x, ...)   \
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_GLUE(                                 \
            /*MA_PP_DEFER(*/op/*)*/,                        \
            /*MA_PP_DEFER(op) needed due to "count" potentially not properly handled by "op" eg: MA_PP_EXPAND which returns all arguments including count*/\
            (count, MA_PP_REMOVE_PARENS(x))         \
        ),                                          \
        MA_PP_GLUE(/*MA_PP_DEFER(*/op/*)*/, (count, x))     \
    )
#define _MA_PP_FOR_EACH_ITER_2(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_1(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_3(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_2(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_4(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_3(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_5(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_4(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_6(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_5(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_7(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_6(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_8(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_7(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_9(count, op, x, ...)       \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_8(MA_PP_INC(count), op, __VA_ARGS__))
#define _MA_PP_FOR_EACH_ITER_10(count, op, x, ...)      \
    MA_PP_IF(                                           \
        MA_PP_IS_PAREN(x),                              \
        MA_PP_GLUE(op, (count, MA_PP_REMOVE_PARENS(x))) \
        ,                                               \
        MA_PP_GLUE(op, (count, x))                      \
    )                                                   \
    MA_PP_EXPAND(_MA_PP_FOR_EACH_ITER_9(MA_PP_INC(count), op, __VA_ARGS__))

#define MA_PP_FOR_EACH_ITER(op, ...)                            \
    /*MA_PP_EXPAND(*/                                               \
        MA_PP_GLUE(                                             \
            MA_PP_OVERLOAD(_MA_PP_FOR_EACH_ITER_, __VA_ARGS__), \
            (0, op, __VA_ARGS__)                                \
        )                                                       \
    /*)*/

#pragma endregion /*for each with single if syntax MA_PP_IF(cond, t, f)*/






//#define MA_PP_FOR_EACH_0(op, x, ...)
//#define MA_PP_FOR_EACH_1(op, x, ...)\
//        MA_PP_GLUE(op, (x))
//#define MA_PP_FOR_EACH_2(op, x, ...)\
//    MA_PP_IF(MA_PP_IS_PAREN(x))(MA_PP_GLUE(op, (MA_PP_REMOVE_PARENS(x))), MA_PP_GLUE(op, (x)))\
//    MA_PP_EXPAND(_MA_PP_FOR_EACH_1(op, __VA_ARGS__))


//#define MA_PP_TEST(op, ...) \
//MA_PP_GLUE(\
//    MA_PP_OVERLOAD(MA_PP_FOR_EACH_, __VA_ARGS__)\
//    ,\
//    (op, __VA_ARGS__)\
//)



#define MA_PP_FOR_EACH_ITER_TEST_0(count, op, ...)
#define MA_PP_FOR_EACH_ITER_TEST_1(count, op, x, ...)\
    MA_PP_IF(                                       \
        MA_PP_IS_PAREN(x),                          \
        MA_PP_OBSTRUCT(MA_PP_OBSTRUCT)(MA_PP_GLUE)  \
        (                                           \
            /*MA_PP_DEFER(*/op/*)*/,                        \
            /*MA_PP_DEFER(op) needed due to "count" potentially not properly handled by "op" eg: MA_PP_EXPAND which returns all arguments including count*/\
            (count, /*MA_PP_OBSTRUCT(*/MA_PP_REMOVE_PARENS/*)*/(x))         \
        ),                                          \
        MA_PP_OBSTRUCT(MA_PP_OBSTRUCT)(MA_PP_GLUE)(/*MA_PP_DEFER(*/op/*)*/, (count, x))     \
    )
#define MA_PP_FOR_EACH_ITER_TEST_2(count, op, x, ...)\
    MA_PP_IF(\
        MA_PP_IS_PAREN(x),\
        MA_PP_OBSTRUCT(MA_PP_OBSTRUCT)(MA_PP_GLUE)(op, (count, MA_PP_REMOVE_PARENS(x)))\
        , \
        MA_PP_OBSTRUCT(MA_PP_OBSTRUCT)(MA_PP_GLUE)(op, (count, x))\
    )\
    MA_PP_EXPAND(MA_PP_FOR_EACH_ITER_TEST_1(MA_PP_INC(count), op, __VA_ARGS__))
///*MA_PP_EXPAND(*/_MA_PP_FOR_EACH_ITER_1(MA_PP_INC(count), op, __VA_ARGS__)/*)*/

#define MA_PP_FOR_EACH_ITER_TEST(op, ...) \
/*MA_PP_GLUE(*/\
    MA_PP_OVERLOAD(MA_PP_FOR_EACH_ITER_TEST_, __VA_ARGS__)\
    /*,*/\
    (0, op, __VA_ARGS__)\
//)
