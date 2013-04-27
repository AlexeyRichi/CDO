/* 
 * File:   connection.h
 * Author: vitor
 *
 * Created on April 17, 2013, 8:13 PM
 */

#ifndef VSQL_CONNECTION_MYSQL_H
#define	VSQL_CONNECTION_MYSQL_H
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <mysql/mysql.h>

namespace VSQL_MYSQL {

    class Connection {
    private:
        std::string host;
        std::string user;
        std::string passwd;
        std::string dbname;
        bool in_transaction;

    public:
        Connection(std::string str_connection);
        bool openConnection();
        bool closeConnection();
        std::string showServerVersion();

    };
}
//PGSQL Version "show server_version"
//MYSQL Version "select VERSION();"
#endif	/* CONNECTION_H */