#pragma once
#include <cstdarg>
#include <string>
//#include <unordered_map>
#include <map>

//#include "common/Common.hpp"
//#include "common/Config.hpp"
#include <malius/core/lang.hpp>
#include <malius/config/ConfigSettings.hpp>
#include <malius/log/SourceInfo.hpp>


//extern ma::config::ConfigSettingInt g_verbosity;


// TODO
// Among those globals are things such as the head and tail pointers to the intrusive linked list of loggers, the string hash database, and the global D3D device.And that�s about it.

namespace ma
{
    namespace log
    {
        // TODO:
        //The log dispatch takes care of registering loggers, and forwards messages to the registered instances.The dispatch itself is nothing more than a namespace.Loggers use an intrusive linked list so that instances can be added / removed in O(1) without any need for a Singleton, pre - main constructors, or similar.

        // TODO: 1. You said in the comments that "The log dispatch takes care of registering loggers, and forwards messages to the registered instances. The dispatch itself is nothing more than a namespace.", what do you mean by "log dispatch", the actual call to eg.  MA_ERROR or  MA_ASSERT? Do you create a new logger for every log message or do you iterate through the list to check if a logger for a specific class/channel already exists?
        // TODO: 2. What do you mean with "The dispatch itself is nothing more than a namespace."
        // TODO: 3. Do the policy classes implement some policy interfaces to ensure that the policies implement those Filter/Format/Write methods?
        // TODO: 4. In order to remove a logger from the list in O(1) it would need to be a doubly linked list, right?

        // 5. In your post about Config data you gave an example usage in which you set a verbosity setting while also

        // log level
        enum class Type : char
        {
            Info    = 1 << 0,
            Warning = 1 << 1,
            Error   = 1 << 2,
            Fatal   = 1 << 3,
            Assert  = 1 << 4
        };

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
            virtual ~Logger(void) { RemoveFromList(); }

            // http://en.cppreference.com/w/cpp/utility/variadic
            // http://en.cppreference.com/w/cpp/language/variadic_arguments
            //template<typename... Args>
            virtual void Log(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args) = 0;

            // As you can see, it�s nothing more than a very simple base class with one virtual function. The arguments are the log-channel (e.g. �TextureManager�, �SoundEngine�, �Memory�, etc), the type of log (e.g. INFO, WARNING, ERROR, FATAL, ASSERT), the verbosity level, a wrapper around source-code information (file name, function name, line number), and last but not least the message itself in terms of a format string and a variable number of arguments. Nothing spectacular so far.

            //template<typename... Args>
            //static void Dispatch(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args &&...*/ va_list args);

            static void Dispatch(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args &&...*/ /*va_list args*/ ...);

        private:
            void AddToList(void);
            void RemoveFromList(void);
            Logger* m_next; // TODO: make this public?
            Logger* m_prev; // for quick removal from list
        };

#define  MA_INFO(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Info, ::ma::log::g_verbosity,  MA_SOURCE_INFO, format, __VA_ARGS__);

#define  MA_WARNING(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Warning, ::ma::log::g_verbosity,  MA_SOURCE_INFO, format, __VA_ARGS__);

#define  MA_ERROR(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Error, ::ma::log::g_verbosity,  MA_SOURCE_INFO, format, __VA_ARGS__);

#define  MA_FATAL(channel, format, ...) \
::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Fatal, ::ma::log::g_verbosity,  MA_SOURCE_INFO, format, __VA_ARGS__);

//#define  MA_ASSERT0(channel, format, ...) \
//::ma::log::Logger::Dispatch(channel, ::ma::log::Type::Assert, ::ma::log::g_verbosity,  MA_SOURCE_INFO, format, __VA_ARGS__);

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
            static  MA_CONSTEXPR size_t size() { return SIZE; }
            char data_[SIZE];
        };

        template <class FilterPolicy, class FormatPolicy, class WritePolicy>
        class LoggerImpl : public Logger
        {
        public:

            LoggerImpl(void) = default;
            LoggerImpl(FilterPolicy&& filter, FormatPolicy&& formatter, WritePolicy&& writer)
            {
                m_filter = std::move(filter);
                m_formatter = std::move(formatter);
                m_writer = std::move(writer);
            }

            virtual void Log(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)  MA_OVERRIDE
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



        //LoggerImpl myLogger(SomeOutputPolicy(arg1, arg2), ChannelFilter(channelToBeShown), OtherPolicy(arg1, arg2, arg3));


        // do additional filtering based on channel, verbosity, etc.

        struct NoFilterPolicy
        {
            //bool Filter(const Criteria& criteria)
            bool Filter(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
            {
                // no filter at all
                return true;
            }
        };

        struct VerbosityFilterPolicy
        {
            bool Filter(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
            {
                // filter based on verbosity
            }
        };

        struct ChannelFilterPolicy
        {
            bool Filter(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
            {
                // filter based on channel
            }
        };

        // Format policies

        struct SimpleFormatPolicy
        {
            /// TODO: Format
            template<size_t T>
            void Format(const Buffer<T>& buffer, const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
            {
                // simple format, e.g. "[TextureManager] the log message";

                std::map<Type, std::string> logType;
                logType.emplace(0, "INFO");
                logType.emplace(1, "WARNING");
                logType.emplace(2, "ERROR");
                logType.emplace(3, "FATAL");
                logType.emplace(4, "ASSERT");
                //logType.at(type);

                //buffer.data =

                // format message
                char msg_format[1024] = "%s(%i): [%s] (%s)\t%s\0";
                char msg[1024];

                ::strncat_s(msg_format, sizeof(msg_format), format, sizeof(msg_format));
                snprintf(msg, sizeof(msg), "%s(%i): [%s] (%s)\t%s", sourceInfo.file, sourceInfo.line, channel, logType.at(type), args);

            }
        };

        struct ExtendedFormatPolicy
        {
            template<size_t T>
            void Format(const Buffer<T>& buffer, const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
            {
                // extended format, e.g. "filename.cpp(10): [TextureManager] (INFO) the log message";
            }
        };

        // Writer policies

        struct IdeWriterPolicy
        {
            template<size_t T>
            void Write(const Buffer<T>& buffer)
            {
                // output to IDE/debugger
#ifdef  MA_COMPILER_MSC
//#   include <debugapi.h>
            //OutputDebugString();
#endif

            /// The IdeLogger outputs all log messages to e.g. the MSVC output window by using OutputDebugString(). In order to do that, it formats the message in a certain kind of way, applies additional filtering based on the channel, verbosity, etc., and finally outputs the message.
            }
        };

        struct ConsoleWriterPolicy
        {
            template<size_t T>
            void Write(const Buffer<T>& buffer)
            {
                // output to the console
            }
        };

        struct FileWriterPolicy
        {
            template<size_t T>
            void Write(const Buffer<T>& buffer)
            {
                // write into a file
            }
        };



        typedef LoggerImpl<NoFilterPolicy, ExtendedFormatPolicy, IdeWriterPolicy> IdeLogger;
        typedef LoggerImpl<VerbosityFilterPolicy, SimpleFormatPolicy, ConsoleWriterPolicy> ConsoleLogger;
        typedef LoggerImpl<NoFilterPolicy, SimpleFormatPolicy, FileWriterPolicy> FileLogger;


        template <class Policy1, class Policy2>
        struct CompositeFilterPolicy
        {
            bool Filter(const Criteria& criteria)
            {
                return (m_policy1.Filter(criteria) && m_policy2.Filter(criteria));
            }

        private:
            Policy1 m_policy1;
            Policy2 m_policy2;
        };

        typedef LoggerImpl<CompositeFilterPolicy<VerbosityFilterPolicy, ChannelFilterPolicy>, ExtendedFormatPolicy, IdeWriterPolicy> FilteredIdeLogger;

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
    }
}
