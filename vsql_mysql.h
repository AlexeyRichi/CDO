/* 
 * File:   connection.h
 * Author: vitor
 *
 * Created on April 17, 2013, 8:13 PM
 */

#ifndef VSQL_CONNECTION_MYSQL_H
#define	VSQL_CONNECTION_MYSQL_H
#define PARAM_STR 1
#define PARAM_INT 2
#define PARAM_FLOAT 3
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <mysql/mysql.h>

namespace VSQL_MYSQL {

    typedef std::map<std::string, std::string> Row;
    typedef std::map<std::string, Row> ResultSet;

     class Statement {
    private:
        std::string _queryString;
        MYSQL * _conn;
        MYSQL_RES * _result_set;
        MYSQL_ROW _mysql_row;
        MYSQL_FIELD * _field;
        Row _row;
        ResultSet _result;
        int _total_rows;
        int _total_cols;
        void clearResultSet();
    public:
        Statement(std::string sql, MYSQL * conn);
        void bindParam(void * value, int data_type);
        void bindValue(std::string param, void * value, int data_type);
        bool execute();
        Row fetch();
        ResultSet fetchAll();
        int rowCount();
        int columnCount();
    };

    class Connection {
    private:
        std::string _host;
        std::string _user;
        std::string _passwd;
        std::string _dbname;
        int _port;
        bool _in_transaction;
        MYSQL * _conn;
        MYSQL_RES * _result_set;
        MYSQL_ROW _mysql_row;
        std::string _error_message;
        void clearResultSet();

    public:
        Connection(std::string host, std::string user, std::string passwd, std::string dbname, int port);
        bool openConnection();
        bool beginTransaction();
        bool savePointTransaction(std::string savePointName);
        bool commitTransaction();
        bool rollbackTransaction();
        bool rollbackTransaction(std::string savepoint);
        bool exec(std::string sql);
        VSQL_MYSQL::Statement * prepare(std::string sql);
        VSQL_MYSQL::Statement * query(std::string sql);
        bool closeConnection();
        std::string getErrorMessage();
    };
}


//PGSQL Version "show server_version"
//MYSQL Version "select VERSION();"
#endif	/* CONNECTION_H */