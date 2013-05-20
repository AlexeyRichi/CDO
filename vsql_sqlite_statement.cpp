#include "vsql_sqlite.h"
#include <boost/algorithm/string.hpp>

VSQL_SQLITE::Statement::Statement(std::string sql, sqlite3* conn) {
    this->_queryString.append(sql);
    this->_conn = conn;
}

void VSQL_SQLITE::Statement::bindParam(void* value, int data_type) {
    char * valor = new char[1000];

    if (data_type == PARAM_INT) {
        sprintf(valor, "%d", *((int *) value));
    } else if (data_type == PARAM_FLOAT) {
        sprintf(valor, "%.2f", *((float *) value));
    } else if (data_type == PARAM_STR) {
        sprintf(valor, "'%s'", (char *) value);
    }

    boost::replace_first(this->_queryString, "?", valor);
    delete(valor);
}

void VSQL_SQLITE::Statement::bindValue(std::string param, void* value, int data_type) {
    char * valor = new char[1000];

    if (data_type == PARAM_INT) {
        sprintf(valor, "%d", *((int *) value));
    } else if (data_type == PARAM_FLOAT) {
        sprintf(valor, "%.2f", *((float *) value));
    } else if (data_type == PARAM_STR) {
        sprintf(valor, "'%s'", (char *) value);
    }

    boost::replace_first(this->_queryString, param, valor);
    delete(valor);
}

int VSQL_SQLITE::Statement::rowCount() {
    return this->_total_rows;
}

int VSQL_SQLITE::Statement::columnCount() {
    return this->_total_cols;
}

void VSQL_SQLITE::Statement::clearResultSet() {
    sqlite3_finalize(this->_result_set);
}
