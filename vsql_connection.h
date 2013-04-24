/* 
 * File:   vsql_connection.h
 * Author: vitor
 *
 * Created on April 23, 2013, 6:56 PM
 */

#ifndef VSQL_CONNECTION_H
#define	VSQL_CONNECTION_H
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <libpq-fe.h>
#include <mysql/mysql.h>

namespace VSQL {

    class VSQLConnection {
    private:
        std::string str_conn;
        bool in_transaction;

    public:
        VSQLConnection(std::string str_connection, const int db_type);
        bool openConnection();
        bool closeConnection();
        std::string showServerVersion();

    };

    //PGSQL Version "show server_version"
    //MYSQL Version "select VERSION();"
};
#endif	/* VSQL_CONNECTION_H */

