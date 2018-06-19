#pragma once
#include <malius/log/SourceInfo.hpp>

namespace ma
{
    struct DebugMessage
    {
        template<typename... Args>
        DebugMessage(const log::SourceInfo& sourceInfo, const char *format, Args&&... args)
        {

        }
    };
}
