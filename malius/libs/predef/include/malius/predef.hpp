/*license info*/

//This library defines a set of compiler, architecture, operating system,
// library, and other version numbers from the information it can gather of C,
//C++ predefined macros or those defined in generally available headers.
//The idea for this library grew out of a proposal to extend the
//Boost Config library to provide more, and consistent, information
//than the feature definitions it supports.

#ifndef  MA_PREDEF_INCLUDE_GUARD
#define  MA_PREDEF_INCLUDE_GUARD

#include "predef/pragma_once.hpp"

#if  MA_PRAGMA_ONCE_SUPPORT
#	pragma once
#endif

#include "predef/os.hpp"
#include "predef/compiler.hpp"
#include "predef/platform.hpp"


#define  MA_STRONGLY_TYPED_ENUMS

#define  MA_INIT_LISTS

//msvc
#ifdef _DEBUG
#	define  MA_DEBUG
#elif NDEBUG
#	define  MA_RELEASE
#endif
//gcc
//#ifdef NDEBUG
//#define  MA_RELEASE
//#else
//#define  MA_DEBUG
//#endif

//#include "malius/config/ConfigSettings.hpp"
//#include "common/config/ConfigSettings.hpp"
// TODO: #include "core/platform/Platform.hpp"


#endif  MA_PREDEF_INCLUDE_GUARD
