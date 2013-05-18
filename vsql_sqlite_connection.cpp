#include "vsql_sqlite.h"

VSQL_SQLITE::Connection::Connection(std::string filename) {
    this->_filename.append(filename);
}

bool VSQL_SQLITE::Connection::openConnection() {
    if (sqlite3_open(this->_filename.c_str(), &this->_conn)) {
        return false;
    } else {
        return true;
    }
}