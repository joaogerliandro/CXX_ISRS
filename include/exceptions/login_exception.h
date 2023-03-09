#pragma once

#include <standard_libs.h>

namespace CXX_ISRS
{
    class LoginException : std::exception
    {
        public:
            LoginException(std::string msg) : message(msg) {}

            std::string what() { return message; }

        private:
            std::string message;
    };
}
