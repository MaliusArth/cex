// scan / macro expansion level control

#pragma once

#include <malius/preprocessor/facilities/expand.hpp>
#pragma region expand

// Reference: http://stackoverflow.com/a/32400131/2190476
//#define MA_PP_EXPAND(...) __VA_ARGS__
//#define MA_PP_EXPAND_SINGLE(x) x


/* **************************************************************************
*                                                                          *
*     (C) Copyright Paul Mensonides 2002.                                  *
*     Distributed under the Boost Software License, Version 1.0. (See      *
*     accompanying file LICENSE_1_0.txt or copy at                         *
*     http://www.boost.org/LICENSE_1_0.txt)                                *
*                                                                          *
************************************************************************** */

//#include <malius/preprocessor/config/config.hpp>

//#define MA_PP_EXPAND_I(x) x
//
//#if ~MA_PP_CONFIG_FLAGS() & MA_PP_CONFIG_MWCC() && ~MA_PP_CONFIG_FLAGS() & MA_PP_CONFIG_DMC()
//#   define MA_PP_EXPAND(x) MA_PP_EXPAND_I(x)
//#else
//#   define MA_PP_EXPAND_OO(par) MA_PP_EXPAND_I ## par
//#   define MA_PP_EXPAND(x) MA_PP_EXPAND_OO((x))
//#endif

#pragma endregion expand

#include <malius/preprocessor/facilities/defer.hpp>
#pragma region defer
//#include <malius/preprocessor/facilities/glue.hpp>

// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
//#define MA_PP_DEFER(id) MA_PP_GLUE(id, MA_PP_EMPTY())
//#define MA_PP_DEFER2(id) id MA_PP_EMPTY()
// Usage:
//#define A() 123
// 1 scan
//int expansionTest = A(); // Expands to 123
// 2 scans
// Expands to A () because it requires one more scan to fully expand
//int deferTest = MA_PP_DEFER(A) ();
//int deferGluedTest = MA_PP_DEFER_GLUED(A) (); // ?
// 1 scan
// Expands to 123, because the EXPAND macro forces another scan
//int deferExpandedTest = MA_PP_EXPAND(MA_PP_DEFER(A) ());
//int deferGluedExpandedTest = MA_PP_EXPAND(MA_PP_DEFER_GLUED(A) ());

#pragma endregion defer

#include <malius/preprocessor/facilities/obstruct.hpp>
#pragma region obstruct

// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
#define MA_PP_OBSTRUCT(...) __VA_ARGS__ MA_PP_DEFER(MA_PP_EMPTY) ()
#define MA_PP_OBSTRUCT_GLUED(...) MA_PP_GLUE(__VA_ARGS__, MA_PP_DEFER_GLUED(MA_PP_EMPTY) ())
// Usage:
//#define A() 123
// 1 scan
//int expansionTest = A(); // Expands to 123
// 2 scans
// Expands to A () because it requires one more scan to fully expand
//int deferTest = MA_PP_DEFER(A) ();
//int deferGluedTest = MA_PP_DEFER_GLUED(A) (); // ?
// 1 scan
// Expands to 123, because the EXPAND macro forces another scan
//int deferExpandedTest = MA_PP_EXPAND(MA_PP_DEFER(A) ());
//int deferGluedExpandedTest = MA_PP_EXPAND(MA_PP_DEFER_GLUED(A) ());
// 3 scans
// Expands to A MA_PP_EMPTY () () because it requires two more scans to fully expand
//int obstructTest = MA_PP_OBSTRUCT(A) ();
//int obstructGluedTest = MA_PP_OBSTRUCT_GLUED(A) ();   // ?

#pragma endregion obstruct
