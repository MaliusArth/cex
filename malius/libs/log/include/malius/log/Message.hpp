#pragma once
#include <malius/log/SourceInfo.hpp>

namespace ma
{
    namespace log
    {
        struct Message
        {
            template<typename... Args>
            Message(const SourceInfo& sourceInfo, const char *format, Args&&... args)
            {

            }
        };
    }
}
