#pragma once

//#include <malius/Config.hpp>
#include <malius/core/lang.hpp>
#include <malius/predef.hpp>

#ifdef MA_OS_WINDOWS
#   include <Windows.h>
//#   include <winbase.h>    // included in windows.h
//#   include <debugapi.h>    // included in winbase.h
#endif

#include <debugbreak/debugbreak.h>  // preprocessor

namespace ma
{
	namespace debug
	{
		//#ifdef _MSC_VER
		//#include <intrin.h>
		//#else
		//#include <csignal>
		//#endif
		//
		//#ifdef _MSC_VER
		//#define MA_BREAKPOINT __debugbreak();   // MS specific intrinsic
		//#else
		//#define MA_BREAKPOINT __builtin_trap();
		////#define MA_BREAKPOINT std::raise(SIGABRT);
		//#endif //_MSC_VER

		/// Windows:
		//__debugbreak();
		//IsDebuggerPresent();

		/// GCC:
		//__builtin_trap();

		/// Android, Linux, Unix:
		//raise(SIGTRAP);


		MA_INLINE bool AreBreakpointsEnabled(void)
		{
//#pragma warning AreBreakpointsEnabled is not implemented.
			return true;
		}

		MA_INLINE bool IsDebuggerConnected(void)
		// MA_INLINE BOOL IsDebuggerConnected(void)
		{
#if defined(MA_OS_WINDOWS) && defined(MA_COMPILER_VC)
			return IsDebuggerPresent();
#else
//#pragma warning IsDebuggerConnected is not implemented for this OS.
			return false;
#endif
		}

// TODO: implement this myself?
#define MA_TOGGLE_BREAKPOINT debug_break()

#if !MA_RELEASE
#   define MA_BREAKPOINT (::ma::debug::AreBreakpointsEnabled() && ::ma::debug::IsDebuggerConnected()) ? MA_TOGGLE_BREAKPOINT : MA_UNUSED(true)
#else
#   define MA_BREAKPOINT MA_UNUSED(true)
#endif

		//MA_LOG0("Flags", "is any set: %d", state.IsAnySet());
		//MA_LOG0("Flags", "are all set: %d", state.AreAllSet());
		//MA_LOG0("Flags", "is Dazed: %d", state.IsSet(PlayerState::Dazed));
		//MA_LOG0("Flags", "is Floating: %d", state.IsSet(PlayerState::Floating));
		//MA_LOG0("Flags", "is Killed: %d", state.IsSet(PlayerState::Killed));
		//PlayerFlags::Description desc = {};
		//MA_LOG0("Flags", "flags have the following state: %s", state.ToString(desc));
	}
}
