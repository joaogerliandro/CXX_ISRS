#pragma once

#include <standard_libs.h>

namespace CXX_ISRS
{
    class Utils
    {
        public:
            static time_t str_to_time(const std::string& str_datetime)
            {
                static const std::string date_time_format{ "%Y-%m-%dT%H:%M:%SZ" };

                std::stringstream string_stream{ str_datetime };

                std::tm date_time;

                string_stream >> std::get_time(&date_time, date_time_format.c_str());

                return std::mktime(&date_time);
            }
    };
}
