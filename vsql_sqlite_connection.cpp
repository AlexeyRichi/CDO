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

void VSQL_SQLITE::Connection::clearResultSet() {
    sqlite3_finalize(this->_result_set);
}

bool VSQL_SQLITE::Connection::closeConnection() {
    sqlite3_close(this->_conn);
    return true;
}

bool VSQL_SQLITE::Connection::exec(std::string sql) {
    if (sqlite3_exec(this->_conn,sql.c_str(),0,0,&this->_error_message)) {
        return false;
    } else {
        return true;
    }
}