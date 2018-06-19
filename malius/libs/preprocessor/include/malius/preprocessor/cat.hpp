#pragma once

// TODO: look into "boost/preprocessor/cat.hpp"
//#include "malius/preprocessor/config/config.hpp"

/// Concatenate preprocessor tokens a and b without expanding macro definitions
/// (however, if invoked from within a macro definition, macro arguments are expanded).
#define MA_PP_CAT_HELPER_HELPER(a, b) a ## b
/// Concatenate preprocessor tokens a and b after macro-expanding them.
#define MA_PP_CAT_HELPER(a, b) MA_PP_CAT_HELPER_HELPER(a, b)
#define MA_PP_CAT(a, b) MA_PP_CAT_HELPER(a, b)
