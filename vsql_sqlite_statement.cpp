
#include <sqlite3.h>

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

bool VSQL_SQLITE::Statement::execute() {
    sqlite3_prepare(this->_conn, this->_queryString.c_str(), -1, &this->_result_set, 0);
    int retorno = sqlite3_step(this->_result_set);
    if (retorno) {
        this->_total_rows = sqlite3_total_changes(this->_conn);
        return true;
    } else {
        this->_error_message = (char *) sqlite3_errmsg(this->_conn);
        return false;
    }
}

VSQL_SQLITE::Row VSQL_SQLITE::Statement::fetch() {

    if (this->_total_rows == 0) {
        sqlite3_reset(this->_result_set);
        int i = 0;
        //Se entrar aqui, a ultima query executa foi realmente um select
        while (sqlite3_step(this->_result_set) == SQLITE_ROW) {
            i++;
        }
        printf("Total de Linhas: %d\n", i);
    }
    return this->_row;
}

VSQL_SQLITE::ResultSet VSQL_SQLITE::Statement::fetchAll() {

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
