/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once

#ifndef  MA_PREDEF_COMPILER_INCLUDE_GUARD
#define  MA_PREDEF_COMPILER_INCLUDE_GUARD

// compiler
#ifdef _MSC_VER
#   define  MA_COMPILER_VC
#endif


#include <malius/predef/compiler/clang.h>
#include <malius/predef/compiler/gcc.h>
#include <malius/predef/compiler/llvm.h>
#include <malius/predef/compiler/vc.h>

#endif //  MA_PREDEF_COMPILER_INCLUDE_GUARD
