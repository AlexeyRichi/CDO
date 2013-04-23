/* 
 * File:   connection.h
 * Author: vitor
 *
 * Created on April 17, 2013, 8:13 PM
 */

#ifndef CONNECTION_H
#define	CONNECTION_H
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <libpq-fe.h>
#include <mysql/mysql.h>

class VSQLConnection {
    
private:
    std::string str_conn;
    int db_type;
    PGconn * pgsql_conn;
    MYSQL * mysql_conn;
    static const int PGSQL_DB = 1;
    static const int MYSQL_DB = 2;
    
public:
    VSQLConnection(std::string str_connection, const int db_type);
    bool openConnection();
    bool closeConnection();
    std::string showServerVersion();
    
};

//PGSQL Version "show server_version"
//MYSQL Version "select VERSION();"
#endif	/* CONNECTION_H */