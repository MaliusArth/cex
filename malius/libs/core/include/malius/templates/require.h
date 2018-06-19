#pragma once
#include <type_traits>

//#define MA_REQUIRES(expr) typename REQUIREMENT = std::enable_if<expr, int>::type
// as non-type template parameter
//#define MA_REQUIRES2(expr) typename std::enable_if<expr, int>::type = 0

#define MA_REQUIRES_NAMED(expr, name) typename name = std::enable_if<expr>::type
#define MA_REQUIRES(expr) typename = std::enable_if<expr>::type
