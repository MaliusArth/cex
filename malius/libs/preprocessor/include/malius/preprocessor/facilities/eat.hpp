#pragma once

#include <malius/preprocessor/config/config.hpp>

/*  MA_PP_EAT */

#if  MA_PP_VARIADICS
#   define  MA_PP_EAT(...)
#else
#   define  MA_PP_EAT(x)
#endif
