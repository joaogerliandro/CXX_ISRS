#pragma once

#include <standard_libs.h>

class User
{
    public:
        uint32_t user_id;
        std::string fullname;
        std::string username;
        std::string password;
        std::string email;
        uint32_t status;
        uint32_t bad_password_count;
        std::string creation_date;
        std::string update_date;
};

