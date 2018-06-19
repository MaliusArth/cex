#pragma once

#include <malius/preprocessor/arithmetic.hpp>
//#include <malius/preprocessor/array.hpp>
#include <malius/preprocessor/cat.hpp>
//#include <malius/preprocessor/comparison.hpp>
//#include <malius/preprocessor/config/limits.hpp>
//#include <malius/preprocessor/control.hpp>
#include <malius/preprocessor/debug.hpp>
#include <malius/preprocessor/facilities.hpp>
//#include <malius/preprocessor/iteration.hpp>
//#include <malius/preprocessor/list.hpp>
//#include <malius/preprocessor/logical.hpp>
//#include <malius/preprocessor/punctuation.hpp>
//#include <malius/preprocessor/repetition.hpp>
//#include <malius/preprocessor/selection.hpp>
//#include <malius/preprocessor/seq.hpp>
//#include <malius/preprocessor/slot.hpp>
#include <malius/preprocessor/stringize.hpp>
//#include <malius/preprocessor/tuple.hpp>
//#include <malius/preprocessor/variadic.hpp>
//#include <malius/preprocessor/wstringize.hpp>

// macro magic utils

// Reference: http://stackoverflow.com/a/9338429/2190476
//#define MA_PP_GLUE(x, y) x y


// scan / macro expansion level control
#include <malius/preprocessor/expansion.hpp>
#pragma region expansion
// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
//#define MA_PP_DEFER(id) MA_PP_GLUE(id, MA_PP_EMPTY())
//#define MA_PP_DEFER2(id) id MA_PP_EMPTY()
//#define MA_PP_OBSTRUCT(...) MA_PP_GLUE(__VA_ARGS__, MA_PP_DEFER(MA_PP_EMPTY)())
//#define MA_PP_OBSTRUCT2(...) __VA_ARGS__ MA_PP_DEFER2(MA_PP_EMPTY)()
// Usage:
//#define A() 123
//int i = A(); // Expands to 123
//int j1 = MA_PP_DEFER(A)(); // Expands to A () because it requires one more scan to fully expand
//int j = MA_PP_DEFER2(A)(); // Expands to A () because it requires one more scan to fully expand
//int k = MA_PP_EXPAND(MA_PP_DEFER(A)()); // Expands to 123, because the EXPAND macro forces another scan
//int l = MA_PP_OBSTRUCT(A)();
//
//int m = MA_PP_OBSTRUCT2(A)();
#pragma endregion expansion

#pragma region detection

// Reference: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms

#include <malius/preprocessor/detail/check.hpp>
//#define MA_PP_CHECK_N(x, n, ...) n
//#define MA_PP_CHECK(...) MA_PP_CHECK_N(__VA_ARGS__, 0)
//#define MA_PP_PROBE(x) x, 1
/* TESTS
//MA_PP_CHECK(MA_PP_PROBE(~)) // Expands to 1
//;
//MA_PP_CHECK(xxx) // Expands to 0
//;
*/


#include <malius/preprocessor/logical/not.hpp>
//#define MA_PP_NOT(x) MA_PP_CHECK(MA_PP_CAT_HELPER(MA_PP_NOT_, x))
//#define MA_PP_NOT_0 MA_PP_PROBE(~)

#include <malius/preprocessor/logical/bool.hpp>
//#define MA_PP_BOOL(x) MA_PP_COMPL(MA_PP_NOT(x))

#include <malius/preprocessor/control/if.hpp>
//#define MA_PP_IF(cond) MA_PP_IIF(MA_PP_BOOL(cond))

#include <malius/preprocessor/control/when.hpp>
//#define MA_PP_WHEN(x) MA_PP_IF(x, MA_PP_EXPAND, MA_PP_EAT)
// TODO: #define MA_PP_WHEN(x) MA_PP_IF(x)(MA_PP_EXPAND, MA_PP_EAT)

#pragma endregion detection

#pragma region comparison

// TODO: test these
//#define MA_PP_COMPARE_foo(x) x
//#define MA_PP_COMPARE_bar(x) x

//#define MA_PP_PRIMITIVE_COMPARE(x, y) \
//MA_PP_IS_PAREN( MA_PP_COMPARE_ ## x ( MA_PP_COMPARE_ ## y) (()) )
//
//#define MA_PP_IS_COMPARABLE(x) MA_PP_IS_PAREN( MA_PP_CAT(MA_PP_COMPARE_, x) (()) )
//
//#define MA_PP_NOT_EQUAL(x, y) \
//MA_PP_IIF(MA_PP_BITAND(MA_PP_IS_COMPARABLE(x))(MA_PP_IS_COMPARABLE(y)) ) \
//( \
//   MA_PP_PRIMITIVE_COMPARE, \
//   1 MA_PP_EAT \
//)(x, y)
//
//#define MA_PP_EQUAL(x, y) MA_PP_COMPL(MA_PP_NOT_EQUAL(x, y))

#pragma endregion comparison

#pragma region multiple parameters

#include <malius/preprocessor/punctuation/remove_parens.hpp>
//#define MA_PP_REMOVE_PARENS(x) MA_PP_EXPAND x
//#define MA_PP_STRIP_PARENS_GLUED(x) MA_PP_GLUE(MA_PP_EXPAND, x)

//#define MA_PP_IS_PAREN_PROBE(...) MA_PP_PROBE(~)
//#define MA_PP_IS_PAREN(x) MA_PP_CHECK(MA_PP_IS_PAREN_PROBE x)
///* TESTS
//// Expands to 1
//MA_PP_IS_PAREN((10,9,8,7,6,5,4,3,2,1))
//;
//// Expands to 0
//MA_PP_IS_PAREN(xxx)
//;
//MA_PP_CHECK(MA_PP_IS_PAREN_PROBE(10, 9, 8, 7, 6, 5, 4, 3, 2, 1))
//;
//MA_PP_CHECK(MA_PP_IS_PAREN_PROBE xxx)
//;
//*/

#pragma endregion multiple parameters

#include <malius/preprocessor/for_each.hpp>
