#pragma once

// tokens

// Reference: http://stackoverflow.com/a/5256500/2190476

/// Turn token into a string literal without expanding macro definitions
/// (however, if invoked from within a macro definition, macro arguments are expanded).
#define  MA_PP_STRINGIZE_NX(token)   #token
/// Turn str into a string literal after macro-expanding it.
#define  MA_PP_STRINGIZE(str)             MA_PP_STRINGIZE_NX(str)

/// Stringizes only if the argument is a macro
/// black magic TODO: learn about (operator ,)
#define  MA_PP_STRINGIZE_MACRO(macro)    \
    ((macro), MA_PP_STRINGIZE_NX(macro))
/// Concatenate preprocessor tokens x and y without expanding macro definitions
/// (however, if invoked from within a macro definition, macro arguments are expanded).
#define  MA_PP_CAT_NX(x, ...)       x##__VA_ARGS__
/// Concatenate preprocessor tokens x and y after macro-expanding them.
#define  MA_PP_CAT(x, ...)               MA_PP_CAT_NX(x, __VA_ARGS__)

// macro magic utils

#define  MA_PP_EMPTY()
#define  MA_PP_EAT(...)
// Reference: http://stackoverflow.com/a/32400131/2190476
#define  MA_PP_EXPAND(...) __VA_ARGS__
// Reference: http://stackoverflow.com/a/9338429/2190476
#define  MA_PP_GLUE(x, y) x y

#define  MA_PP_STRIP_PARENS(x)  MA_PP_GLUE( MA_PP_EXPAND, x)
//#define  MA_PP_STRIP_PARENS(x)  MA_PP_EXPAND x

// scan / macro expansion level control

// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
#define  MA_PP_DEFER(id)  MA_PP_GLUE(id,  MA_PP_EMPTY())
#define  MA_PP_DEFER2(id) id  MA_PP_EMPTY()
#define  MA_PP_OBSTRUCT(...)  MA_PP_GLUE(__VA_ARGS__,  MA_PP_DEFER( MA_PP_EMPTY)())
#define  MA_PP_OBSTRUCT2(...) __VA_ARGS__  MA_PP_DEFER2( MA_PP_EMPTY)()
// Usage:
//#define A() 123
//int i = A(); // Expands to 123
//int j1 =  MA_PP_DEFER(A)(); // Expands to A () because it requires one more scan to fully expand
//int j =  MA_PP_DEFER2(A)(); // Expands to A () because it requires one more scan to fully expand
//int k =  MA_PP_EXPAND( MA_PP_DEFER(A)()); // Expands to 123, because the EXPAND macro forces another scan
//int l =  MA_PP_OBSTRUCT(A)();
//
//int m =  MA_PP_OBSTRUCT2(A)();





// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms

// pattern matching

#define  MA_PP_IIF(cond)  MA_PP_CAT_NX( MA_PP_IIF_, cond)
#define  MA_PP_IIF_0(t, ...) __VA_ARGS__
#define  MA_PP_IIF_1(t, ...) t

/// complement
#define  MA_PP_COMPL(b)  MA_PP_CAT_NX( MA_PP_COMPL_, b)
#define  MA_PP_COMPL_0 1
#define  MA_PP_COMPL_1 0

#define  MA_PP_BITAND(x)  MA_PP_CAT_NX( MA_PP_BITAND_, x)
#define  MA_PP_BITAND_0(y) 0
#define  MA_PP_BITAND_1(y) y

#define  MA_PP_INC(x)  MA_PP_CAT_NX( MA_PP_INC_, x)
#define  MA_PP_INC_0 1
#define  MA_PP_INC_1 2
#define  MA_PP_INC_2 3
#define  MA_PP_INC_3 4
#define  MA_PP_INC_4 5
#define  MA_PP_INC_5 6
#define  MA_PP_INC_6 7
#define  MA_PP_INC_7 8
#define  MA_PP_INC_8 9
#define  MA_PP_INC_9 9

#define  MA_PP_DEC(x)  MA_PP_CAT_NX( MA_PP_DEC_, x)
#define  MA_PP_DEC_0 0
#define  MA_PP_DEC_1 0
#define  MA_PP_DEC_2 1
#define  MA_PP_DEC_3 2
#define  MA_PP_DEC_4 3
#define  MA_PP_DEC_5 4
#define  MA_PP_DEC_6 5
#define  MA_PP_DEC_7 6
#define  MA_PP_DEC_8 7
#define  MA_PP_DEC_9 8

// detection

#define  MA_PP_CHECK_N(x, n, ...) n
#define  MA_PP_CHECK(...)  MA_PP_CHECK_N(__VA_ARGS__, 0)
#define  MA_PP_PROBE(x) x, 1
// MA_PP_CHECK( MA_PP_PROBE(~)) // Expands to 1
//;
// MA_PP_CHECK(xxx) // Expands to 0
//;

#define  MA_PP_IS_PAREN_PROBE(...)  MA_PP_PROBE(~)
#define  MA_PP_IS_PAREN(x)  MA_PP_CHECK( MA_PP_IS_PAREN_PROBE x)
// MA_PP_IS_PAREN((10,9,8,7,6,5,4,3,2,1)) // Expands to 1
//;
// MA_PP_IS_PAREN(xxx) // Expands to 0
//;
// MA_PP_CHECK_N( MA_PP_IS_PAREN_PROBE xxx, 0)
//;

#define  MA_PP_NOT(x)  MA_PP_CHECK( MA_PP_CAT_NX( MA_PP_NOT_, x))
#define  MA_PP_NOT_0  MA_PP_PROBE(~)

#define  MA_PP_BOOL(x)  MA_PP_COMPL( MA_PP_NOT(x))

#define  MA_PP_IF(cond)  MA_PP_IIF( MA_PP_BOOL(cond))

#define  MA_PP_WHEN(x)  MA_PP_IF(x)( MA_PP_EXPAND,  MA_PP_EAT)

//#define  MA_PP_TEST1(name) int name;
//
//     MA_PP_FOR_EACH( MA_PP_TEST1, (test1))

//#define  MA_PP_TEST2(name, value) int name = value;

//     MA_PP_GLUE( MA_PP_TEST2, (test4, 7))  MA_PP_EXPAND( MA_PP_FOR_EACH_2( MA_PP_TEST2, (test5, 13), (test6, 28)))
//
//    std::printf("with macro %d %d %d %d %d %d\n",  MA_PP_STRIP_PARENS((5, 6, 7, 8, 9, 10)));
//    std::printf("with macro %d\n",  MA_PP_STRIP_PARENS(10));
//
//     MA_PP_IF( MA_PP_IS_PAREN(x))(op x, op(x))
//
//#define  MA_PP_A(a) int a;
//#define  MA_PP_B(b) int b;
//     MA_PP_IIF_0( MA_PP_A(x),  MA_PP_B(y))
//
//     MA_PP_A( MA_PP_EXPAND(x))
//     MA_PP_GLUE( MA_PP_B, (b))
//     MA_PP_STRIP_PARENS((5, 6, 7, 8, 9, 10));


// comparison
// TODO: test these
//#define  MA_PP_COMPARE_foo(x) x
//#define  MA_PP_COMPARE_bar(x) x

#define  MA_PP_PRIMITIVE_COMPARE(x, y) \
 MA_PP_IS_PAREN(  MA_PP_COMPARE_ ## x (  MA_PP_COMPARE_ ## y) (()) )

#define  MA_PP_IS_COMPARABLE(x)  MA_PP_IS_PAREN(  MA_PP_CAT( MA_PP_COMPARE_, x) (()) )

#define  MA_PP_NOT_EQUAL(x, y) \
 MA_PP_IIF( MA_PP_BITAND( MA_PP_IS_COMPARABLE(x))( MA_PP_IS_COMPARABLE(y)) ) \
( \
    MA_PP_PRIMITIVE_COMPARE, \
   1  MA_PP_EAT \
)(x, y)

#define  MA_PP_EQUAL(x, y)  MA_PP_COMPL( MA_PP_NOT_EQUAL(x, y))


// variadic macros

// TODO: https://codecraft.co/2014/11/25/variadic-macros-tricks/

//  MA_PP_COUNT_ARGS() is a very nifty macro to retrieve the number of arguments handed to a variable-argument macro
// unfortunately, VS 2010 still has this compiler bug which treats a __VA_ARGS__ argument as being one single parameter:
// https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details
#if _MSC_VER >= 1400 /*&& _MSC_VER < 1900*/
// Accept any number of args >= N, but expand to just the Nth one. The macro 
#   define _ MA_PP_GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N

// Count how many args are in a variadic macro. We now use MSVC/GCC/Clang's extension to 
// handle the case where ... expands to nothing. We must add a placeholder arg before 
// ##__VA_ARGS__ (its value is totally irrelevant, but it's necessary to preserve 
// the shifting offset we want). In addition, we must add 0 as a valid value to be in 
 // the N position. 
#   define  MA_PP_COUNT_ARGS(...) \
     MA_PP_EXPAND( _ MA_PP_GET_NTH_ARG("ignored", ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#else
#   define _ MA_PP_GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N

// Count how many args are in a variadic macro. We now use MSVC/GCC/Clang's extension to 
// handle the case where ... expands to nothing. We must add a placeholder arg before 
// ##__VA_ARGS__ (its value is totally irrelevant, but it's necessary to preserve 
// the shifting offset we want). In addition, we must add 0 as a valid value to be in 
// the N position. 
#   define  MA_PP_COUNT_ARGS(...) \
    _ MA_PP_GET_NTH_ARG("ignored", ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

//  MA_PP_PASS_VA_ARGS passes __VA_ARGS__ as multiple parameters to another macro, working around the above-mentioned bug
//#if _MSC_VER >= 1400 /*&& _MSC_VER < 1900*/
//#   define  MA_PP_PASS_VA_ARGS(...) \
//     MA_PP_EXPAND(__VA_ARGS__)
//#else
//#   define  MA_PP_PASS_VA_ARGS(...) __VA_ARGS__
//#endif

#define  MA_PP_CALL_VA_MACRO(macro_prefix, ...)\
 MA_PP_CAT(macro_prefix,  MA_PP_COUNT_ARGS(__VA_ARGS__))

#include <algorithm>

#define  MA_MAX_2(a, b)          std::max(a, b)
#define  MA_MAX_3(a, b, c)        MA_MAX_2( MA_MAX_2(a, b), c)
#define  MA_MAX_4(a, b, c, d)     MA_MAX_2( MA_MAX_3(a, b, c), d)

#define  MA_MAX(...)      MA_PP_EXPAND( MA_PP_GLUE( MA_PP_CALL_VA_MACRO( MA_MAX_, __VA_ARGS__), (__VA_ARGS__)))


///////////////////////////////////////////////////////
// TODO: test these
//#define  MA_PP_GET_ARGS(f,args,...) args
//#define  MA_PP_FOR_EACH_1(op, count, x, ...) \
// MA_PP_IF( MA_PP_EQUAL( MA_PP_COUNT_ARGS( MA_PP_STRIP_PARENS(x)), 2)\
//( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x),  MA_PP_GET_ARGS( MA_PP_STRIP_PARENS(x)))),\
// MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count)))\
// MA_PP_EAT(__VA_ARGS__)




//#define _ MA_PP_FOR_EACH_0(op, count, x, ...) /*\
//     MA_PP_EAT(__VA_ARGS__)*/
//#define _ MA_PP_FOR_EACH_1(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count)) /*\
//     MA_PP_EAT(__VA_ARGS__)*/
//#define _ MA_PP_FOR_EACH_2(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count)) \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_1(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_3(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count)) \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_2(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_4(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count))  \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_3(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_5(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count))  \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_4(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_6(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count))  \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_5(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_7(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count))  \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_6(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_8(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count))  \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_7(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_9(op, count, x, ...) \
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count))  \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_8(op,  MA_PP_INC(count), __VA_ARGS__))
//#define _ MA_PP_FOR_EACH_10(op, count, x, ...)\
//     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count))  \
//     MA_PP_EXPAND(_ MA_PP_FOR_EACH_9(op,  MA_PP_INC(count), __VA_ARGS__))
//
//#define  MA_PP_FOR_EACH(op, ...)\
// MA_PP_EXPAND(\
//     MA_PP_GLUE(\
//         MA_PP_CALL_VA_MACRO(_ MA_PP_FOR_EACH_, __VA_ARGS__),\
//        (op, 0, __VA_ARGS__)\
//    )\
//)
//#define  MA_PP_FOR_EACH(op, ...)\
// MA_PP_EXPAND(\
//     MA_PP_CALL_VA_MACRO(_ MA_PP_FOR_EACH_, __VA_ARGS__)\
//    (op, 0, __VA_ARGS__)\
//)





//#define _ MA_PP_FOR_EACH_0(op, count, x, ...)
//#define _ MA_PP_FOR_EACH_1(op, count, x, ...)\
//     MA_PP_IF( MA_PP_IS_PAREN(x))             \
//    (                                       \
//        op( MA_PP_STRIP_PARENS(x), count)    \
//    ,                                       \
//        op(x, count)                        \
//    )
//#define _ MA_PP_FOR_EACH_2(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_1(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_3(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_2(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_4(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_3(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_5(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_4(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_6(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_5(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_7(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_6(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_8(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_7(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_9(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_8(op,  MA_PP_INC(count), __VA_ARGS__)
//#define _ MA_PP_FOR_EACH_10(op, count, x, ...)    \
//    _ MA_PP_FOR_EACH_1(op, count, x, __VA_ARGS__)    \
//    _ MA_PP_FOR_EACH_9(op,  MA_PP_INC(count), __VA_ARGS__)
//
//#define  MA_PP_FOR_EACH(op, ...)\
// MA_PP_EXPAND(\
//     MA_PP_GLUE(\
//         MA_PP_CALL_VA_MACRO(_ MA_PP_FOR_EACH_, __VA_ARGS__),\
//        (op, 0, __VA_ARGS__)\
//    )\
//)

//#define  MA_PP_APPLY(x, y) x(y)


// TODO:  MA_PP_FOR_EACH (w/o iterater)
#define _ MA_PP_FOR_EACH_0(op, x, ...)
#define _ MA_PP_FOR_EACH_1(op, x, ...)\
     MA_PP_IF( MA_PP_IS_PAREN(x))             \
    (                                       \
/* MA_PP_DEFER(op) needed due to "count" potentially not properly handled by "op" eg:  MA_PP_EXPAND which returns all arguments including count*/\
         MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x)))    \
    ,                                       \
         MA_PP_GLUE(op, (x))                        \
    )
#define _ MA_PP_FOR_EACH_2(op, x, ...)\
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_1(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_3(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_2(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_4(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_3(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_5(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_4(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_6(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_5(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_7(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_6(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_8(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_7(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_9(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_8(op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_10(op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x))),  MA_PP_GLUE(op, (x)))\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_9(op, __VA_ARGS__))

#define  MA_PP_FOR_EACH(op, ...)\
 MA_PP_EXPAND(\
     MA_PP_GLUE(\
         MA_PP_CALL_VA_MACRO(_ MA_PP_FOR_EACH_, __VA_ARGS__),\
        (op, __VA_ARGS__)\
    )\
)




// TODO:  MA_PP_FOR_EACH_ITER (passes the iterater to op as first argument)
#define _ MA_PP_FOR_EACH_ITER_0(count, op, x, ...)
#define _ MA_PP_FOR_EACH_ITER_1(count, op, x, ...)\
     MA_PP_IF( MA_PP_IS_PAREN(x))             \
    (                                       \
         MA_PP_GLUE( MA_PP_DEFER(op), /* MA_PP_DEFER(op) needed due to "count" potentially not properly handled by "op" eg:  MA_PP_EXPAND which returns all arguments including count*/(count,  MA_PP_STRIP_PARENS(x)))    \
    ,                                       \
         MA_PP_GLUE( MA_PP_DEFER(op), (count, x))                        \
    )
#define _ MA_PP_FOR_EACH_ITER_2(count, op, x, ...)\
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        , \
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_1( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_3(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_2( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_4(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_3( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_5(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_4( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_6(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_5( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_7(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_6( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_8(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_7( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_9(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_8( MA_PP_INC(count), op, __VA_ARGS__))
#define _ MA_PP_FOR_EACH_ITER_10(count, op, x, ...)    \
     MA_PP_IF( MA_PP_IS_PAREN(x))\
    (\
         MA_PP_GLUE(op, (count,  MA_PP_STRIP_PARENS(x)))\
        ,\
         MA_PP_GLUE(op, (count, x))\
    )\
     MA_PP_EXPAND(_ MA_PP_FOR_EACH_ITER_9( MA_PP_INC(count), op, __VA_ARGS__))

#define  MA_PP_FOR_EACH_ITER(op, ...)\
/* MA_PP_EXPAND(*/\
     MA_PP_GLUE(\
         MA_PP_CALL_VA_MACRO(_ MA_PP_FOR_EACH_ITER_, __VA_ARGS__),\
        (0, op, __VA_ARGS__)\
    /*)*/\
)


///////////////////////////////////////////////////////



// expanding variadic arguments
#define  MA_PP_FOR_EACH_SIMPLE_2(op, a1, a2) op(a1, 0) op(a2, 1)
#define  MA_PP_FOR_EACH_SIMPLE_3(op, a1, a2, a3) op(a1, 0) op(a2, 1) op(a3, 2)
#define  MA_PP_FOR_EACH_SIMPLE_4(op, a1, a2, a3, a4) op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3)
#define  MA_PP_FOR_EACH_SIMPLE_5(op, a1, a2, a3, a4, a5) op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4)
#define  MA_PP_FOR_EACH_SIMPLE_6(op, a1, a2, a3, a4, a5, a6) op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5)
#define  MA_PP_FOR_EACH_SIMPLE_7(op, a1, a2, a3, a4, a5, a6, a7) op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6)
#define  MA_PP_FOR_EACH_SIMPLE_8(op, a1, a2, a3, a4, a5, a6, a7, a8) op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7)
#define  MA_PP_FOR_EACH_SIMPLE_9(op, a1, a2, a3, a4, a5, a6, a7, a8, a9) op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8)
#define  MA_PP_FOR_EACH_SIMPLE_10(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9)

#define  MA_PP_FOR_EACH_SIMPLE(op, ...) \
 MA_PP_EXPAND(\
     MA_PP_GLUE(\
         MA_PP_CALL_VA_MACRO( MA_PP_FOR_EACH_SIMPLE_, __VA_ARGS__),\
        (op, __VA_ARGS__)\
    )\
)
