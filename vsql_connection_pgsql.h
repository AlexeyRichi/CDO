/* 
 * File:   query.h
 * Author: vitor
 *
 * Created on April 17, 2013, 8:22 PM
 */

#ifndef VSQL_CONNECTION_PGSQL_H
#define	VSQL_CONNECTION_PGSQL_H
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <libpq-fe.h>

namespace VSQL_PGSQL {

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

#endif	/* QUERY_H */

