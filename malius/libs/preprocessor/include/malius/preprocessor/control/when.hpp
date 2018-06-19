#pragma once

#include <malius/preprocessor/control/if.hpp>
#include <malius/preprocessor/facilities/expand.hpp>
#include <malius/preprocessor/facilities/eat.hpp>

#define  MA_PP_WHEN(x)  MA_PP_IF(x,  MA_PP_EXPAND,  MA_PP_EAT)
// TODO: #define  MA_PP_WHEN(x)  MA_PP_IF(x)( MA_PP_EXPAND,  MA_PP_EAT)

// TESTS
// Expands to nothing
// MA_PP_WHEN(0) (123)
// Expands to 123
// MA_PP_WHEN(1) (123)
