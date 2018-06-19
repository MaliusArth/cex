#pragma once
#include <stdexcept>

namespace ma
{
    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException(void) : logic_error("Function not yet implemented.") {}
        //explicit NotImplementedException(const std::string& message)
        //    : logic_error(message) {}

        //explicit NotImplementedException(const char* message)
        //    : logic_error(message) {}

        //char const * what() const override { return "Function not yet implemented."; }
    };
}
