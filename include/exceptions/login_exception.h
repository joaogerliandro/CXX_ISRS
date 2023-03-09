#pragma once

#include <standard_libs.h>
#include <enums/exception_enums.h>

namespace CXX_ISRS
{
    class LoginException : std::exception
    {
        public:
            LoginException(std::string msg, CXX_ISRS::ExceptionType ex_type) : message(msg), exception_type(ex_type) {}

            std::string what() { return message; }

            CXX_ISRS::ExceptionType what_type() { return exception_type; }

        private:
            std::string message;

            CXX_ISRS::ExceptionType exception_type;
    };
}
