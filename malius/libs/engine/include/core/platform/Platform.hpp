#pragma once

// compiler
#ifdef _MSC_VER
#   define  MA_COMPILER_MSC
#endif

// platform
#ifdef _WINDOWS
#include "core/platform/WindowsPlatform.hpp"
#endif