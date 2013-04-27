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
#include <map>
#include <vector>
#include <libpq-fe.h>

namespace VSQL_PGSQL {

    typedef std::vector<std::string> Row;
    typedef std::map<std::string, Row> ResultSet;

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

    class Statement {
    private:
        std::string _queryString;
    public:
        void bindParam(int param, void * value, int data_type);
        void bindValue(std::string param, void * value, int data_type);
        bool execute();
        Row fetch();
        ResultSet fetchAll();
        void * fetchObject();
        int rowCount();
        int columnCount();
    };
}

#endif	/* QUERY_H */

