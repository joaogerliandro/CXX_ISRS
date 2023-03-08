#pragma once

#include <common.h>
#include <entities/user.h>

class UserDAO
{
    public:
        UserDAO(sql::Connection *con) : dao_con(con) {}

        User get_user_by_username(std::string username)
        {
            try
            {
                User user;

                sql::PreparedStatement *pstmt = dao_con->prepareStatement("SELECT * FROM User WHERE Username = ?");
                pstmt->setString(1, username);

                sql::ResultSet *res = pstmt->executeQuery();

                while(res->next())
                {
                    user = {
                        .user_id  = res->getInt("UserID"),
                        .fullname = res->getString("Fullname"),
                        .username = res->getString("Username"),
                        .password = res->getString("Password")
                    };
                }

                delete pstmt;
                delete res;

                return user;
            }
            catch (sql::SQLException &ex)
            {
                std::cout << "[ERROR]: "            << ex.what()
                          << " (MySQL error code: " << ex.getErrorCode()
                          << ", SQLState: "         << ex.getSQLState()
                          << " )"                   << std::endl;
            }
        }

    private:
        sql::Connection *dao_con;
};

