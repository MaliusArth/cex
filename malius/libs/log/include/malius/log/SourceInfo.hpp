#pragma once

#if !defined(__func__)
#   if defined(_MSC_VER)
#       define __func__ __FUNCTION__
#   else
#       define __func__ __PRETTY_FUNCTION__
#   endif
#endif

namespace ma
{
    namespace log
    {
        struct SourceInfo
        {
            SourceInfo(const char* source_file, const char* source_func, int source_line) : file(source_file), func(source_func), line(source_line) {}
            const char* file;
            const char* func;
            int line;
        };
    }
#define MA_SOURCE_INFO ::ma::log::SourceInfo(__FILE__, __func__, __LINE__)
}