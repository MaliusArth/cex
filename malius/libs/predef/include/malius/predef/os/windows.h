/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#pragma once

#ifndef  MA_PREDEF_OS_WINDOWS_INCLUDE_GUARD
#define  MA_PREDEF_OS_WINDOWS_INCLUDE_GUARD

//#include <malius/predef/version_number.h>
#include "./../version_number.h"

// TODO: C:\Users\MaliusArth\Malius\Projects\ext\repos\modular-boost\libs\predef\include\boost\predef\detail

#if !defined( MA_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(_WIN32) || defined(_WIN64) || \
    defined(__WIN32__) || defined(__TOS_WIN__) || \
    defined(__WINDOWS__) \
    )
#   undef  MA_OS_WINDOWS
#   define  MA_OS_WINDOWS  MA_VERSION_NUMBER_AVAILABLE
#endif

#if  MA_OS_WINDOWS
#   define  MA_OS_WINDOWS_AVAILABLE
//#   include <malius/predef/detail/os_detected.h>
#   include "./../detail/os_detected.h"
#endif

#define  MA_OS_WINDOWS_NAME "Microsoft Windows"

#endif  MA_PREDEF_OS_WINDOWS_INCLUDE_GUARD