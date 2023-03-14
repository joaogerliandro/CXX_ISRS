#pragma once

#include <common.h>
#include <entities/user.h>
#include <exceptions/login_exception.h>
#include <utils.h>

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
                        .user_id            = res->getUInt("UserID"),
                        .fullname           = res->getString("Fullname"),
                        .username           = res->getString("Username"),
                        .password           = res->getString("Password"),
                        .email              = res->getString("Email"),
                        .status             = res->getUInt("Status"),
                        .bad_password_count = res->getUInt("BadPasswordCount"),
                        .creation_date      = res->getString("CreationDate"),
                        .update_date        = res->getString("UpdateDate")
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

        void update_user(User& user)
        {
            try
            {
                sql::PreparedStatement *pstmt = dao_con->prepareStatement("UPDATE User "
                                                                          "SET Fullname = ?, Username = ?, Password = ?,"
                                                                          " Email = ?, Status = ?, BadPasswordCount = ?,"
                                                                          " UpdateDate = NOW() WHERE UserID =  ?");
                pstmt->setString(1, user.fullname);
                pstmt->setString(2, user.username);
                pstmt->setString(3, user.password);
                pstmt->setString(4, user.email);
                pstmt->setUInt(5, user.status);
                pstmt->setUInt(6, user.bad_password_count);
                pstmt->setUInt(7, user.user_id);

                pstmt->execute();

                delete pstmt;
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

