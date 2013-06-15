#include "vsql_sqlite.h"

VSQL_SQLITE::Connection::Connection(std::string filename) {
    this->_filename.append(filename);
}

bool VSQL_SQLITE::Connection::openConnection() {
    //Se o banco não existir ele cria um novo.
    if (sqlite3_open(this->_filename.c_str(), &this->_conn)) {
        return false;
    } else {
        return true;
    }
}

bool VSQL_SQLITE::Connection::beginTransaction() {
    if (sqlite3_exec(this->_conn, "begin transaction;", 0, 0, &this->_error_message)) {
        return false;
    } else {
        return true;
    }
}

bool VSQL_SQLITE::Connection::commitTransaction() {
    if (sqlite3_exec(this->_conn, "commit transaction;", 0, 0, &this->_error_message)) {
        return false;
    } else {
        return true;
    }
}

bool VSQL_SQLITE::Connection::rollbackTransaction() {
    if (sqlite3_exec(this->_conn, "rollback transaction;", 0, 0, &this->_error_message)) {
        return false;
    } else {
        return true;
    }
}

bool VSQL_SQLITE::Connection::rollbackTransaction(std::string savepoint) {
    char * sql = new char[300];
    sprintf(sql, "rollback to '%s'", savepoint.c_str());
    if (sqlite3_exec(this->_conn, sql, 0, 0, &this->_error_message)) {
        delete(sql);
        return false;
    } else {
        delete(sql);
        return true;
    }
}

bool VSQL_SQLITE::Connection::savePointTransaction(std::string savePointName) {
    char * sql = new char[300];
    sprintf(sql, "savepoint '%s'", savePointName.c_str());
    if (sqlite3_exec(this->_conn, sql, 0, 0, &this->_error_message)) {
        delete(sql);
        return false;
    } else {
        delete(sql);
        return true;
    }
}

bool VSQL_SQLITE::Connection::exec(std::string sql) {
    if (sqlite3_exec(this->_conn, sql.c_str(), 0, 0, &this->_error_message)) {
        return false;
    } else {
        return true;
    }
}

VSQL_SQLITE::Statement * VSQL_SQLITE::Connection::query(std::string sql) {
    VSQL_SQLITE::Statement * stm;
    stm = new VSQL_SQLITE::Statement(sql, this->_conn);
    stm->execute();
    return stm;
}

VSQL_SQLITE::Statement * VSQL_SQLITE::Connection::prepare(std::string sql) {
    VSQL_SQLITE::Statement * stm;
    stm = new VSQL_SQLITE::Statement(sql, this->_conn);
    return stm;
}

char *VSQL_SQLITE::Connection::getErrorMessage() {
    return this->_error_message;
}

void VSQL_SQLITE::Connection::clearResultSet() {
    sqlite3_finalize(this->_result_set);
}

bool VSQL_SQLITE::Connection::closeConnection() {
    sqlite3_close(this->_conn);
    return true;
}