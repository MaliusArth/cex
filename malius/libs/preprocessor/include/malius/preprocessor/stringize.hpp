#pragma once

//#include "malius/preprocessor/config/config.hpp"

// Reference: http://stackoverflow.com/a/5256500/2190476

/// Turn token into a string literal without expanding macro definitions
/// (however, if invoked from within a macro definition, macro arguments are expanded).
#define MA_PP_STRINGIZE_NX(token)   #token
/// Turn str into a string literal after macro-expanding it.
#define MA_PP_STRINGIZE(str) MA_PP_STRINGIZE_NX(str)

/// Stringizes only if the argument is a macro
/// black magic TODO: learn about (, operator)
#define MA_PP_STRINGIZE_MACRO(macro)    \
    ((macro), MA_PP_STRINGIZE_NX(macro))



// Reference: "boost/preprocessor/stringize.hpp"
//#if MA_PP_CONFIG_FLAGS() & MA_PP_CONFIG_MSVC()
//#define MA_PP_STRINGIZE_I(text) #text
//
//#define MA_PP_STRINGIZE_A(arg) MA_PP_STRINGIZE_I arg
//#define MA_PP_STRINGIZE(text) MA_PP_STRINGIZE_A((text))

//#endif
