#pragma once

#include <malius/preprocessor/cat.hpp>
#include <malius/preprocessor/variadic/size.hpp>
#include <malius/preprocessor/facilities/defer.hpp>

//  MA_PP_OVERLOAD

#if  MA_PP_VARIADICS

#    define  MA_PP_OVERLOAD(prefix, ...)\
     MA_PP_CAT(prefix,  MA_PP_VARIADIC_SIZE(__VA_ARGS__))

#endif
