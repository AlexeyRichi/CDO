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
        sqlite3_stmt * _result_set;
        Row _row;
        ResultSet _result;
        int _total_rows;
        int _total_cols;
        void clearResultSet();
    public:
        Statement(std::string sql, sqlite3 * conn);
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
        std::string _filename;
        bool _in_transaction;
        sqlite3 * _conn;
        sqlite3_stmt * _result_set;
        char * _error_message;
        void clearResultSet();

    public:
        Connection(std::string filename);
        bool openConnection();
        bool beginTransaction();
        bool savePointTransaction(std::string savePointName);
        bool commitTransaction();
        bool rollbackTransaction();
        bool rollbackTransaction(std::string savepoint);
        bool exec(std::string sql);
        VSQL_SQLITE::Statement * prepare(std::string sql);
        VSQL_SQLITE::Statement * query(std::string sql);
        bool closeConnection();
        char * getErrorMessage();
    };
}

#endif	/* VSQL_SQLITE_H */

