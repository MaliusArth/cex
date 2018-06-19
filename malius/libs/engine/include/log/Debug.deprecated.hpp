#pragma once

#include "common/Config.hpp"
#ifdef  MA_PLATFORM_WIN
#   include <winbase.h>    // included in windows.h
#endif

#include <debugbreak/debugbreak.h>  // preprocessor
#include "common/Common.hpp"

namespace ma
{
    namespace ide
    {
        
    }
    namespace debug
    {
        //#ifdef _MSC_VER
        //#include <intrin.h>
        //#else
        //#include <csignal>
        //#endif
        //
        //#ifdef _MSC_VER
        //#define  MA_BREAKPOINT __debugbreak();   // MS specific intrinsic
        //#else
        //#define  MA_BREAKPOINT __builtin_trap();
        ////#define  MA_BREAKPOINT std::raise(SIGABRT);
        //#endif //_MSC_VER

         MA_INLINE bool IsDebuggerConnected(void)
        {
#if defined( MA_PLATFORM_WIN) && defined( MA_COMPILER_MSC)
            return IsDebuggerPresent();
#else
            return false;
#endif
        }

#if ! MA_RELEASE
#   define  MA_BREAKPOINT   \
(ma::debug::IsDebuggerConnected() ? debug_break() :  MA_UNUSED(true))
#else
#   define  MA_BREAKPOINT  MA_UNUSED(true)
#endif


// MA_LOG0("Flags", "is any set: %d", state.IsAnySet());
// MA_LOG0("Flags", "are all set: %d", state.AreAllSet());
// MA_LOG0("Flags", "is Dazed: %d", state.IsSet(PlayerState::Dazed));
// MA_LOG0("Flags", "is Floating: %d", state.IsSet(PlayerState::Floating));
// MA_LOG0("Flags", "is Killed: %d", state.IsSet(PlayerState::Killed));
//PlayerFlags::Description desc = {};
// MA_LOG0("Flags", "flags have the following state: %s", state.ToString(desc));
    }
}
