#pragma once

#include <malius/log/Logger.hpp>

#include <cstdio>
#include <cstring>

namespace ma
{
	namespace log
	{

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

		// Verbosity vs Type:
		// Type: Error, eg. "Error: Something really bad happend"
		// Verbosity: amount of detail about errors, eg. 
		// "filepath:line:column: Error: Something really bad happend" (verbosity=0)
		// "filepath:line:column: Error: some additional information about the error" (verbosity=1)
		// "filepath:line:column: Error: here is the stacktrace related to the error: ..." (verbosity=2)
		struct VerbosityFilterPolicy
		{
			VerbosityFilterPolicy(void)
				: filteredVerbosity(2)
			{}
			VerbosityFilterPolicy(size_t verbosity)
				: filteredVerbosity(verbosity)
			{}
			bool Filter(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
			{
				// filter based on verbosity
				if (filteredVerbosity >= verbosity)
				{
					return true;
				}
				return false;
			}

			size_t filteredVerbosity;
		};

		struct ChannelFilterPolicy
		{
			ChannelFilterPolicy(const char* channel)
				: filteredChannel(channel)
			{}

			bool Filter(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
			{
				// filter based on channel
				if (strcmp(channel, filteredChannel))
				{
					return true;
				}
				return true;
			}

			const char* filteredChannel;
		};

		// Format policies

		namespace
		{
			static const char* typeStringLUT[5] = {"INFO", "WARNING", "ERROR", "FATAL", "ASSERT"};
		}

		struct SimpleFormatPolicy
		{
			/// TODO: Format
			template<size_t T>
			void Format(
				MA_OUT Buffer<T>& buffer, 
				const char* channel, Type type, size_t verbosity, 
				const SourceInfo& sourceInfo, 
				const char* format, /*Args ...*/ va_list args
			)
			{
				// simple format, e.g. "[TextureManager] the log message";
/* 				const char*
				std::map<Type, std::string> logType;
				logType.emplace(Type::Info, "INFO");
				logType.emplace(Type::Warning, "WARNING");
				logType.emplace(Type::Error, "ERROR");
				logType.emplace(Type::Fatal, "FATAL");
				logType.emplace(Type::Assert, "ASSERT"); */
				//logType.at(type);

				// format message
				char full_format[T];
				char msg[T] = "%s(%i): [%s] (%s)\t";

				// size_t msg_size = strlen(format);
				// std::printf("%zu", msg_size);

				// char const *testStr = typeStringLUT[static_cast<size_t>(type)];

				snprintf(full_format, T, msg, 
					sourceInfo.file, sourceInfo.line, 
					channel, typeStringLUT[static_cast<size_t>(type)],
					format);

#if MA_COMPILER_VC
				::strncat_s(msg_format, sizeof(msg_format), format, sizeof(msg_format));
#else
				::strncat(full_format, format, sizeof(full_format) - strlen(full_format) - 1);
#endif
				vsnprintf(msg, T, full_format, args);

				//vsnprintf(msg, T, msg_format,
				//	sourceInfo.file, sourceInfo.line, channel, typeStringLUT[static_cast<size_t>(type)-1u],
				//	args);
				// snprintf(msg, T, "%s(%i): [%s] (%s)\t%s", sourceInfo.file, sourceInfo.line, channel, typeStringLUT[type-1], args);

				int test = strlen(msg);
				::strncpy(buffer.data, msg, T);
				// ::memcpy(msg, buffer.data, strlen(msg));
			}
		};

		//struct ExtendedFormatPolicy
		//{
		//	template<size_t T>
		//	void Format(const Buffer<T>& buffer, const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
		//	{
		//		// extended format, e.g. "filename.cpp(10): [TextureManager] (INFO) the log message";
		//	}
		//};

		// Writer policies

//		struct IdeWriterPolicy
//		{
//			template<size_t T>
//			void Write(const Buffer<T>& buffer)
//			{
//				// output to IDE/debugger
//#ifdef MA_COMPILER_VC
//				//#   include <debugapi.h>
//				//OutputDebugString();
//#endif
//			}
//		};

		struct ConsoleWriterPolicy
		{
			template<size_t T>
			void Write(const Buffer<T>& buffer)
			{
				// output to the console
				std::printf("%s\n", buffer.data);
			}
		};

//		struct FileWriterPolicy
//		{
//			template<size_t T>
//			void Write(const Buffer<T>& buffer)
//			{
//				// write into a file
//			}
//		};


		// The IdeLogger outputs all log messages to e.g.
		// the MSVC output window by using OutputDebugString().
		// In order to do that, it formats the message in a certain kind of way,
		// applies additional filtering based on the channel, verbosity, etc.,
		// and finally outputs the message.
		// typedef LoggerImpl<NoFilterPolicy, ExtendedFormatPolicy, IdeWriterPolicy> IdeLogger;
		typedef LoggerImpl<VerbosityFilterPolicy, SimpleFormatPolicy, ConsoleWriterPolicy> ConsoleLogger;
		// typedef LoggerImpl<NoFilterPolicy, SimpleFormatPolicy, FileWriterPolicy> FileLogger;

		template <class Policy1, class Policy2>
		struct CompositeFilterPolicy
		{
			// bool Filter(const Criteria& criteria)
			bool Filter(const char* channel, Type type, size_t verbosity, const SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
			{
				// return (m_policy1.Filter(criteria) && m_policy2.Filter(criteria));
				return (m_policy1.Filter(channel, type, verbosity, sourceInfo, format, args)
					 && m_policy2.Filter(channel, type, verbosity, sourceInfo, format, args));
			}

		private:
			Policy1 m_policy1;
			Policy2 m_policy2;
		};

		// typedef LoggerImpl<CompositeFilterPolicy<VerbosityFilterPolicy, ChannelFilterPolicy>, ExtendedFormatPolicy, IdeWriterPolicy> FilteredIdeLogger;

	}
}
