//#include <malius/config/ConfigSettings.hpp>
#include <malius/Config.hpp>
#include <malius/log/Logger.hpp>
//#include "log/Logger.hpp"
//#include <malius/config/ConfigSettingInt.hpp>

namespace ma
{
namespace log
{
//::ma::config::ConfigSettingInt
//	g_verbosity("Verbosity",
//				"Defines the verbosity level of logging operations", 0, 0, 2);

namespace
{
// intrusive list
static Logger *head = nullptr;
static Logger *tail = nullptr;
} // namespace

// namespace dispatch
//{
//    void Log(const char* channel, size_t type, size_t verbosity, const
//    SourceInfo& sourceInfo, const char* format, /*Args ...*/ va_list args)
//    {

//        Logger* iterPtr = head;
//        for (iterPtr = head; iterPtr != nullptr;)
//        {
//            iterPtr = iterPtr->m_next;
//        }
//    }
//}
// template<typename... Args>
// void Logger::Dispatch(const char* channel, Type type, size_t verbosity, const
// SourceInfo& sourceInfo, const char* format, /*Args&& ...*/ va_list args)
//{
//    Logger* iterPtr = head;
//    for (iterPtr = head; iterPtr != nullptr;)
//    {
//        iterPtr->Log(channel, type, verbosity, sourceInfo, format,
//        /*std::forward<Args>(args)...*/ args); iterPtr = iterPtr->m_next;
//    }
//}

//namespace dispatch
//{
//void Log(const char *channel, Type type, size_t verbosity,
//		 const SourceInfo &sourceInfo, const char *format,
//		 /*Args&& ...*/ /*va_list args*/...)
//{
//	va_list list;
//	va_start(list, format);
//	Logger *iterPtr = head;
//	for (iterPtr = head; iterPtr != nullptr;)
//	{
//		iterPtr->Log(channel, type, verbosity, sourceInfo, format,
//					 /*std::forward<Args>(args)...*/ list);
//		iterPtr++;
//	}
//	va_end(list);
//}
//} // namespace dispatch

Logger::~Logger(void) { RemoveFromList(); }

void Logger::Dispatch(const char *channel, Type type, size_t verbosity,
					  const SourceInfo &sourceInfo, const char *format,
					  /*Args&& ...*/ /*va_list args*/...)
{
	va_list list;
	va_start(list, format);
	Logger *iterPtr = head;
	for (iterPtr = head; iterPtr != nullptr;)
	{
		iterPtr->Log(channel, type, verbosity, sourceInfo, format,
					 /*std::forward<Args>(args)...*/ list);
		iterPtr = iterPtr->m_next;
	}
	va_end(list);
}

void Logger::AddToList(void)
{
	if (head)
	{
		tail->m_next = this;
		// TODO: Malius added this but is it neccessary? ... yes
		m_prev = tail;
		tail = this;
	}
	else
	{
		head = this;
		tail = this;
	}
}

void Logger::RemoveFromList(void)
{
	if (head == this)
	{
		m_next->m_prev = nullptr;
		head = m_next;
	}
	else
	{
		m_prev->m_next = m_next;
		if (m_next)
		{
			m_next->m_prev = m_prev;
		}
	}
}
} // namespace log
} // namespace ma
