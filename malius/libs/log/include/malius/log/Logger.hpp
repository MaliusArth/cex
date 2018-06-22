#pragma once
//#include <malius/predef/compiler.hpp>
//#include "common/Config.hpp"
#include <malius/core/lang.hpp>
// #include <malius/preprocessor/facilities/overload.hpp>
#include <malius/config/ConfigSettings.hpp>
#include <malius/log/SourceInfo.hpp>

#include <cstdarg>
#include <string>
//#include <unordered_map>
#include <map>


//extern ma::config::ConfigSettingInt g_verbosity;


// TODO
// Stefan Reinalter: "Among those globals are things such as the head and tail pointers to the intrusive linked list of loggers, the string hash database, and the global D3D device. And that's about it."

namespace ma
{
	namespace log
	{
		// log level
		// enum class Type : char
		// {
			// Info    = 1 << 0,
			// Warning = 1 << 1,
			// Error   = 1 << 2,
			// Fatal   = 1 << 3,
			// Assert  = 1 << 4
		// };
		enum class Type : size_t
		{
			Info    = 0,
			Warning = 1,
			Error   = 2,
			Fatal   = 3,
			Assert  = 4
		};

		// TODO:
		//The log dispatch takes care of registering loggers, and forwards messages to the registered instances.The dispatch itself is nothing more than a namespace.Loggers use an intrusive linked list so that instances can be added / removed in O(1) without any need for a Singleton, pre - main constructors, or similar.

		// Reference: https://blog.molecular-matters.com/2011/06/24/hashed-strings/
		// me::core::logDispatch::Log

//		namespace dispatch
//		{
//			void Log(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args&& ...*/ /*va_list args*/ ...);
//		}

// TODO:
// Reference: https://blog.molecular-matters.com/2011/06/29/designing-extensible-modular-classes/
// The log dispatch is a namespace that offers functions for logging messages, warnings, errors, etc. It simply forwards the message in question to all registered loggers. Loggers themselves are stored in an intrusive linked list, so there is no need for a singleton, a global std::vector, or similar.
// The log macros #define to either a call to any of the functions offered by the log dispatch namespace, or “nothing” (with a bit of extra magic to suppress warnings about unused function arguments and the likes). This ensures that certain logs do not generate *any* instructions in the final executable if I don’t want to.
// There are also additional log macros for e.g. logging a message every N-th time, logging only once, etc.

		// TODO: 1. You said in the comments that "The log dispatch takes care of registering loggers, and forwards messages to the registered instances. The dispatch itself is nothing more than a namespace.", what do you mean by "log dispatch", the actual call to eg. MA_ERROR or MA_ASSERT? Do you create a new logger for every log message or do you iterate through the list to check if a logger for a specific class/channel already exists?
		// TODO: 2. What do you mean with "The dispatch itself is nothing more than a namespace."
		// TODO: 3. Do the policy classes implement some policy interfaces to ensure that the policies implement those Filter/Format/Write methods?
		// TODO: 4. In order to remove a logger from the list in O(1) it would need to be a doubly linked list, right?

		// 5. In your post about Config data you gave an example usage in which you set a verbosity setting while also


		// Reference: http://stackoverflow.com/questions/10422034/when-to-use-extern-in-c
		extern config::ConfigSettingInt g_verbosity;

		//void test(void)
		//{
		//    // coding using the config value
		//    if (g_verbosity > 1)
		//    {
		//        // whatever
		//    }
		//}

		class Logger
		{
		public:
			Logger(void)
				: m_next(nullptr)
				, m_prev(nullptr)
			{
				AddToList();
			}
			// TODO: remove logger from intrusive list
			virtual ~Logger(void);// { RemoveFromList(); }

			// http://en.cppreference.com/w/cpp/utility/variadic
			// http://en.cppreference.com/w/cpp/language/variadic_arguments
			//template<typename... Args>
			virtual void Log(
				const char* channel, Type type, size_t verbosity,
				const SourceInfo& sourceInfo,
				const char* format, /*Args ...*/ va_list args) = 0;

			// As you can see, it's nothing more than a very simple base class with one virtual function. The arguments are the log-channel (e.g. "TextureManager", "SoundEngine", "Memory", etc), the type of log (e.g. INFO, WARNING, ERROR, FATAL, ASSERT), the verbosity level, a wrapper around source-code information (file name, function name, line number), and last but not least the message itself in terms of a format string and a variable number of arguments. Nothing spectacular so far.

			//template<typename... Args>
			//static void Dispatch(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args &&...*/ va_list args);
			static void Dispatch(
				const char* channel, Type type, size_t verbosity,
				const SourceInfo& sourceInfo,
				const char* format, /*Args &&...*/ /*va_list args*/ ...);

		private:
			void AddToList(void);
			void RemoveFromList(void);
			Logger* m_next; // TODO: make this public?
			Logger* m_prev; // for quick removal from list
		};


//////////////////////////////////////////////////////////////////////
// TODO: 
//Reference: https://stackoverflow.com/a/35214790
//Reference: https://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/

/* #define COMMA_IF_PARENS(...) ,
#define LPAREN (
#define EXPAND(...) __VA_ARGS__
#define CHOOSE(...) \
    EXPAND(LOG LPAREN \
      __VA_ARGS__ COMMA_IF_PARENS __VA_ARGS__ COMMA_IF_PARENS __VA_ARGS__ (), \
      LOG2, impossible, LOG2, LOG1, LOG0, LOG1, ))
#define LOG(a0, a1, a2, a3, a4, a5, arg, ...) arg

#define TestDebug(...) CHOOSE(__VA_ARGS__)(__VA_ARGS__)

// TestDebug(1,2,3,4,5,6,7,8,9,0);
*/

// #define MA_INFO_0()
// #define MA_INFO(channel, format, ...) MA_PP_OVERLOAD(MA_INFO_, __VA_ARGS__)

#define MA_INF0(channel, format) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Info, ::ma::log::g_verbosity, MA_SOURCE_INFO, format);
#define MA_INFO(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Info, ::ma::log::g_verbosity, MA_SOURCE_INFO, format, __VA_ARGS__);

#define MA_WARNING(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Warning, ::ma::log::g_verbosity, MA_SOURCE_INFO, format, __VA_ARGS__);

#define MA_ERROR(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Error, ::ma::log::g_verbosity, MA_SOURCE_INFO, format, __VA_ARGS__);

#define MA_FATAL(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Fatal, ::ma::log::g_verbosity, MA_SOURCE_INFO, format, __VA_ARGS__);

//#define MA_ASSERT0(channel, format, ...) \
//::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Assert, ::ma::log::g_verbosity, MA_SOURCE_INFO, format, __VA_ARGS__);




		struct Criteria
		{
			//Criteria(const char* m_channel, size_t m_type, size_t m_verbosity, const SourceInfo& source_info, const char* format)
			//    : m_channel(m_channel),
			//      m_type(m_type),
			//      m_verbosity(m_verbosity),
			//      sourceInfo(source_info),
			//      format(format) {}

			const char* m_channel;
			size_t m_type, m_verbosity;
			//const SourceInfo& sourceInfo;
			//const char* format;
			//va_list args;
		};


		//struct FilterPolicy
		//{
		//    virtual ~FilterPolicy() {}

		//    virtual bool Filter(const Criteria& criteria) = 0;
		//};

		template<size_t SIZE>
		struct Buffer
		{
			static MA_CONSTEXPR size_t size() { return SIZE; };
			char data[SIZE];
		};

		template <class FilterPolicy, class FormatPolicy, class WritePolicy>
		class LoggerImpl : public Logger
		{
		public:
			LoggerImpl(void) = default;
			LoggerImpl(
				FilterPolicy&& filter,
				FormatPolicy&& formatter,
				WritePolicy&& writer
			)
			 : m_filter(std::move(filter)),
			   m_formatter(std::move(formatter)),
			   m_writer(std::move(writer))
			{
				// m_filter = std::move(filter);
				// m_formatter = std::move(formatter);
				// m_writer = std::move(writer);
			}

			virtual void Log(
				const char* channel, Type type, size_t verbosity,
				const SourceInfo& sourceInfo,
				const char* format, /*Args ...*/ va_list args
			) MA_OVERRIDE
			{
				if (m_filter.Filter(channel, type, verbosity, sourceInfo, format, args))
				{
					//char buffer[1024];
					Buffer<1024> buffer;
					m_formatter.Format(buffer, channel, type, verbosity, sourceInfo, format, args);
					m_writer.Write(buffer);
				}

				//Criteria criteria = { channel, type, verbosity/*, sourceInfo, format, args*/ };
				//if (m_filter.Filter(criteria))
				//{
				//    Buffer buffer;
				//    m_formatter.Format(buffer, criteria, format, args);
				//    m_writer.Write(buffer);
				//}
			}

		private:
			FilterPolicy m_filter;
			FormatPolicy m_formatter;
			WritePolicy m_writer;
		};
	}
}

#include <malius/log/LoggerPolicies.inl>