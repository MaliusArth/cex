#pragma once
//#include <malius/log/Logger.hpp>
#include <malius/log/SourceInfo.hpp>

//#include <malius/preprocessor.hpp>
#include <malius/core/breakpoint.hpp>
#include <malius/preprocessor/stringize.hpp>
#include <malius/preprocessor/for_each.hpp>

// temp
#include <iostream>
//#include <cstdarg>

namespace ma
{
	// Reference: https://blog.molecular-matters.com/2011/07/22/an-improved-assert/

	/// Forwards everything to the logger(s)
	/// and the installed assertion handler(s).
	class Assert
	{
		const log::SourceInfo& m_sourceInfo;
	public:
		// logs the formatted message
		Assert(const log::SourceInfo& sourceInfo, const char* format, ...);

		Assert& Variable(const char* const name, bool var);

		Assert& Variable(const char* const name, char var);

		Assert& Variable(const char* const name, short var);

		Assert& Variable(const char* const name, int var);

		// more overloads for built-in types...

		// generic
		/// TODO: implement generic Variable
		template <typename T>
		Assert& Variable(const char* const name, const T& value)
		{
			return *this;
		};
	};
}

#define  MA_ASSERT_MACRO_TOGGLE 0

#define  MA_ASSERT_IMPL_VAR(variable) .Variable( MA_PP_STRINGIZE(variable), variable)
	//#define  MA_ASSERT_IMPL_VARS(...)              MA_PP_EXPAND_ARGS  MA_PP_PASS_ARGS( MA_ASSERT_IMPL_VAR, __VA_ARGS__),  MA_BREAKPOINT)
	//#define  MA_OPEN_PAREN (
	//#define  MA_CLOSE_PAREN )

#if  MA_ASSERT_MACRO_TOGGLE
#define  MA_ASSERT_IMPL_VARS(...)\
 MA_PP_FOR_EACH( MA_ASSERT_IMPL_VAR, __VA_ARGS__),  MA_BREAKPOINT)
	// MA_PP_EXPAND(( MA_ASSERT_IMPL_VAR, __VA_ARGS__),  MA_BREAKPOINT)

#define  MA_ASSERT(condition, format, ...)\
	(condition) ?  MA_UNUSED(true) : (::ma::Assert( MA_SOURCE_INFO, "Assertion \"" #condition "\" failed. " format, __VA_ARGS__)  MA_ASSERT_IMPL_VARS
#else

#include <malius/preprocessor/variadic/pass_va.hpp>
//#include <malius/preprocessor/facilities/expand.hpp>

#define  MA_ASSERT_IMPL_VARS(...)\
	 MA_PP_FOR_EACH_SIMPLE  MA_PP_PASS_VA( MA_ASSERT_IMPL_VAR, __VA_ARGS__) ,  MA_BREAKPOINT  MA_PP_CLOSE_PAREN
	// MA_PP_EXPAND(( MA_ASSERT_IMPL_VAR, __VA_ARGS__) ,  MA_BREAKPOINT)

#define  MA_ASSERT(condition, format, ...)\
	(condition) ?  MA_UNUSED(true) :  MA_PP_OPEN_PAREN ::ma::Assert( MA_SOURCE_INFO, "Assertion \"" #condition "\" failed. " format, __VA_ARGS__)  MA_ASSERT_IMPL_VARS
#endif // MA_ASSERT_MACRO_TOGGLE
