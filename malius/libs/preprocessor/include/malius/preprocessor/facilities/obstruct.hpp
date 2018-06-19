#pragma once

#include <malius/preprocessor/facilities/defer.hpp>

// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
#define  MA_PP_OBSTRUCT(...) __VA_ARGS__  MA_PP_DEFER( MA_PP_EMPTY) ()
#define  MA_PP_OBSTRUCT_GLUED(...)  MA_PP_GLUE(__VA_ARGS__,  MA_PP_DEFER_GLUED( MA_PP_EMPTY) ())
// Usage:
//#define A() 123
// 1 scan
//int expansionTest = A(); // Expands to 123
// 2 scans
// Expands to A () because it requires one more scan to fully expand
//int deferTest =  MA_PP_DEFER(A) ();
//int deferGluedTest =  MA_PP_DEFER_GLUED(A) (); // ?
// 1 scan
// Expands to 123, because the EXPAND macro forces another scan
//int deferExpandedTest =  MA_PP_EXPAND( MA_PP_DEFER(A) ());
//int deferGluedExpandedTest =  MA_PP_EXPAND( MA_PP_DEFER_GLUED(A) ());
// 3 scans
// Expands to A  MA_PP_EMPTY () () because it requires two more scans to fully expand
//int obstructTest =  MA_PP_OBSTRUCT(A) ();
//int obstructGluedTest =  MA_PP_OBSTRUCT_GLUED(A) ();   // ?
