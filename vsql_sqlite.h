/* 
 * File:   vsql_sqlite.h
 * Author: vitor
 *
 * Created on May 18, 2013, 9:46 AM
 */

#ifndef VSQL_SQLITE_H
#define	VSQL_SQLITE_H
#include <sqlite3.h>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>


namespace VSQL_SQLITE {
    typedef std::map<std::string, std::string> Row;
    typedef std::map<int, Row> ResultSet;

    class Statement {
    private:
        std::string _queryString;
        sqlite3 * _conn;
        PGresult * _result_set;
        Row _row;
        ResultSet _result;
        int _total_rows;
        int _total_cols;
        void clearResultSet();
    public:
        Statement(std::string sql, PGconn * conn);
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
        PGconn * _conn;
        PGresult * _result_set;
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
        VSQL_PGSQL::Statement * prepare(std::string sql);
        VSQL_PGSQL::Statement * query(std::string sql);
        bool closeConnection();
        std::string getErrorMessage();
        std::string getServerVersion();
    };
}

#endif	/* VSQL_SQLITE_H */

