#pragma once

#include <malius/preprocessor/config/config.hpp>
//#include <malius/preprocessor/cat.hpp>

// TODO: https://codecraft.co/2014/11/25/variadic-macros-tricks/

//  MA_PP_VARIADIC_SIZE
////  MA_PP_COUNT_ARGS
////  MA_PP_GET_NTH

//  MA_PP_VARIADIC_SIZE() is a very nifty macro to retrieve the number of arguments handed to a variable-argument macro
// unfortunately, VS 2015 still has this compiler bug which treats a __VA_ARGS__ argument as being one single parameter:
// https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details

#if  MA_PP_VARIADICS

// Accept any number of args >= N, but expand to just the Nth argument.
#   define  MA_PP_VARIADIC_SIZE_I(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, size, ...) size

// Count how many args are in a variadic macro. We now use MSVC/GCC/Clang's extension to 
// handle the case where ... expands to nothing. We must add a placeholder arg before 
// ##__VA_ARGS__ (its value is totally irrelevant, but it's necessary to preserve 
// the shifting offset we want). In addition, we must add 0 as a valid value to be in 
// the N position.

#   if  MA_PP_VARIADICS_MSVC
#include <malius/preprocessor/facilities/expand.hpp>
#include <malius/preprocessor/variadic/pass_va.hpp>

#       define  MA_PP_VARIADIC_SIZE(...) \
    /* MA_PP_EXPAND(*/\
         MA_PP_VARIADIC_SIZE_I  MA_PP_OPEN_PAREN 0, ##__VA_ARGS__, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0  MA_PP_CLOSE_PAREN\
    /*)*/
#   else
#       define  MA_PP_VARIADIC_SIZE(...)  MA_PP_VARIADIC_SIZE_I(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,)
#   endif
#endif