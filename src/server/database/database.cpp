#include "database.hpp"

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cstring>

using namespace net;

server::database::database(sql::Driver *driver, sql::Connection *con, const char *hostname, const char *username, const char *password)
{
    this->driver = driver;
    this->con = con;
    this->__credentials = new credentials(hostname, username, password);
}

sql::Connection *server::database::getCon(void) const noexcept
{
    return con;
}

sql::Driver *server::database::getDriver(void) const noexcept
{
    return driver;
}

server::database::credentials::credentials(const char *hostname, const char *username, const char *password)
{
    this->hostname = strdup(hostname);
    this->username = strdup(username);
    this->password = strdup(password);
}

char *server::database::credentials::getHostname(void) const noexcept
{
    return const_cast<char *>(hostname);
}

char *server::database::credentials::getUsername(void) const noexcept
{
    return const_cast<char *>(username);
}

char *server::database::credentials::getPassword(void) const noexcept
{
    return const_cast<char *>(password);
}

int server::database::credentials::getCredentials(char *hostname, char *username, char *password)
{
    std::cout << "hostname: ";
    std::cin.get(hostname, LENGHT);

    size_t len = strlen(hostname);

    if (len > HOSTNAME_LENGHT || len == 0)
        return EXIT_FAILURE;

    std::cin.get();
    std::cout << "username: ";
    std::cin.get(username, LENGHT);

    len = strlen(username);

    if (len > USERNAME_LENGHT || len == 0)
        return EXIT_FAILURE;

    std::cin.get();
    std::cout << "password: ";
    std::cin.get(password, LENGHT);

    len = strlen(password);

    if (len > PASSWORD_LENGHT || len == 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

bool server::database::fetchTables(void)
{
    return EXIT_SUCCESS;
}

server::database::~database()
{
    delete __credentials;
    con->close();
    delete con;
}

server::database::credentials::~credentials()
{
    free(hostname);
    free(username);
    free(password);
}