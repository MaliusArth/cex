#pragma once

// std lib
#include <cstdarg>
// temp
#include <iostream>

// external libs
#include <malius/log/Logger.hpp>

#include <malius/preprocessor.hpp>
//#include <malius/core/debug.hpp>
//#include <malius/log/Debug.hpp>

// internal lib
#include <malius/assert/Assert.hpp>
//#include <malius/assert/SourceInfo.hpp>

namespace ma
{
	// logs the formatted message
	Assert::Assert(const log::SourceInfo& sourceInfo, const char* format, ...) : m_sourceInfo(sourceInfo)
	{
		//using namespace log;
		//auto testLogger = LoggerImpl<NoFilterPolicy, SimpleFormatPolicy, IdeWriterPolicy>();

		//testLogger.Log("Assert", ma::log::Type::Assert, g_verbosity, sourceInfo, format, list);

		va_list list;
		va_start(list, format);

		// MA_WARNING("Assert", 0u, g_verbosity, sourceInfo, format, list);

		// Reference: https://blog.molecular-matters.com/2014/05/10/using-runtime-compiled-c-code-as-a-scripting-language-under-the-hood/
		// MA_ERROR("ScriptSupport", "An exception has been caught, forcing the script to be disabled. See the log output for more details.");

		//"Config", "Could not set value %d for setting \"%s\" because it is smaller than the minimum. It will be set to %d.", value, m_name, m_min


		std::clog << "clog" << std::endl;
		std::cerr << "cerr" << std::endl;
		std::cout << "cout" << std::endl;


		::ma::log::Logger::Dispatch("Assert", ma::log::Type::Assert, log::g_verbosity, m_sourceInfo, format, list);
		va_end(list);
		/*  MA_LOG:
		..\src\Core\Platform\ProcessorInfo.cpp(417): [Assert] (ASSERT) Assertion "a > b" failed. a was not less than b, sadly*/
	}

	Assert& Assert::Variable(const char* const name, bool var)
	{
		va_list list;
		va_start(list, name);
		char msg[64] = "o Variable ";
		::strncat_s(msg, sizeof(msg), name, sizeof(name));
		::strncat_s(msg, sizeof(msg), " = %s", sizeof(" = %s"));

		::ma::log::Logger::Dispatch("Assert", ::ma::log::Type::Assert, log::g_verbosity, m_sourceInfo, msg, (var ? "true" : "false"));
		va_end(list);
		/*  MA_LOG:
		..\src\Core\Platform\ProcessorInfo.cpp(417): [Assert] (ASSERT)   o Variable a = 10 (int)
		..\src\Core\Platform\ProcessorInfo.cpp(417): [Assert] (ASSERT)   o Variable b = 20 (int)
		*/

		return *this;
	}

	Assert& Assert::Variable(const char* const name, char var)
	{
		va_list list;
		va_start(list, name);
		char msg[64] = "o Variable ";
		::strncat_s(msg, sizeof(msg), name, sizeof(name));
		::strncat_s(msg, sizeof(msg), " = %c", sizeof(" = %c"));

		::ma::log::Logger::Dispatch("Assert", ::ma::log::Type::Assert, ::ma::log::g_verbosity, m_sourceInfo, msg, list);
		va_end(list);

		return *this;
	}

	Assert& Assert::Variable(const char* const name, short var)
	{
		va_list list;
		va_start(list, name);
		char msg[64] = "o Variable ";
		::strncat_s(msg, sizeof(msg), name, sizeof(name));
		::strncat_s(msg, sizeof(msg), " = %h", sizeof(" = %h"));

		::ma::log::Logger::Dispatch("Assert", ::ma::log::Type::Assert, ::ma::log::g_verbosity, m_sourceInfo, msg, list);
		va_end(list);

		return *this;
	}

	Assert& Assert::Variable(const char* const name, int var)
	{
		va_list list;
		va_start(list, name);
		char msg[64] = "o Variable ";
		::strncat_s(msg, sizeof(msg), name, sizeof(name));
		::strncat_s(msg, sizeof(msg), " = %d", sizeof(" = %d"));

		::ma::log::Logger::Dispatch("Assert", ::ma::log::Type::Assert, ::ma::log::g_verbosity, m_sourceInfo, msg, list);
		va_end(list);

		return *this;
	}

	inline void test1234()
	{
		std::string str = "some string";
		int test1 = 7;
		int test2 = 13;

		//_ MA_PP_FOR_EACH( MA_ASSERT_IMPL_VAR, (str.c_str()), (test1), (test2));


		//_ MA_PP_FOR_EACH( MA_ASSERT_IMPL_VAR, str.c_str(), test1);


		//_ MA_PP_FOR_EACH( MA_ASSERT_IMPL_VAR, (str.c_str()));


		//_ MA_PP_FOR_EACH( MA_ASSERT_IMPL_VAR, str.c_str());

		// TODO: reinalter: Visual Studio gives errors in some more complex macros eg. DECLARE_FLAGS even though they expand into proper code, how do you handle this?

		//int i =  MA_PP_VARIADIC_SIZE(1, 5, 3, 7);

		// MA_PP_VARIADIC_SIZE()
		// MA_PP_OVERLOAD(qweet) ()
			// MA_PP_CAT(prefix,  MA_PP_VARIADIC_SIZE())

			// MA_PP_GLUE( MA_PP_OVERLOAD(qweet), (op));

		// MA_PP_FOR_EACH_SIMPLE(qweet, 1)

		// TODO:
		 MA_ASSERT(false, "Assert: %i", 42) ();


		 MA_ASSERT(false, "Assert: %i", 42) (str.c_str(), test1);


		 MA_ASSERT(false, "Assert: %i", 42) (str.c_str());


		 MA_ASSERT(false, "Assert: %i %s", 42, "test") (str.c_str());


		// MA_PP_EXPAND( MA_PP_GLUE( MA_PP_REMOVE_PARENS((char* vag1 =, "vagina")), 0));

		// MA_PP_EXPAND( MA_PP_DEFER( MA_PP_GLUE)( MA_PP_REMOVE_PARENS((char* vag2 =, "vagina"))));

		// MA_PP_IIF_1 (  MA_PP_GLUE( MA_PP_REMOVE_PARENS((char* vag3 = , "vagina")), 0) ,  MA_PP_GLUE((char* vag = , "vagina"), 0) );

		//_ MA_PP_FOR_EACH_2(_ MA_PP_FOR_EACH_0, "penis");

	}
}
