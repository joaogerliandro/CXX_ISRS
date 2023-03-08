#include "mainwindow.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

int main(int argc, char *argv[])
{
    try
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        driver = get_driver_instance();
        con = driver->connect("hostname", "username", "password");

        con->setSchema("cxx_isrs");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM User");

        while (res->next())
        {
            std::cout << "UserId: " << res->getInt("UserID") << std::endl;
            std::cout << "Fullname: " << res->getString("Fullname") << std::endl;
            std::cout << "Username: " << res->getString("Username") << std::endl;
            std::cout << "Password: " << res->getString("Password") << std::endl;

            std::cout << std::endl;
        }

        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &ex)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << ex.what();
        std::cout << " (MySQL error code: " << ex.getErrorCode();
        std::cout << ", SQLState: " << ex.getSQLState() << " )" << std::endl;
    }

    QApplication a(argc, argv);
    MainWindow window;

    window.show();
    return a.exec();
}
