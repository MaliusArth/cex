#pragma once

#include <malius/preprocessor/logical/compl.hpp>
#include <malius/preprocessor/logical/not_any.hpp>

#define  MA_PP_BOOL_ANY(x)  MA_PP_COMPL( MA_PP_NOT_ANY(x))

// MA_PP_BOOL_ANY(0)
// MA_PP_BOOL_ANY(1)
// MA_PP_BOOL_ANY(7)
// MA_PP_BOOL_ANY(anything)