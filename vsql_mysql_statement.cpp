#include "vsql_mysql.h"
#include <boost/algorithm/string.hpp>

VSQL_MYSQL::Statement::Statement(std::string sql, MYSQL* conn) {
    this->_queryString.append(sql);
    this->_conn = conn;
}

void VSQL_MYSQL::Statement::bindParam(void* value, int data_type) {
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

void VSQL_MYSQL::Statement::bindValue(std::string param, void* value, int data_type) {
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

bool VSQL_MYSQL::Statement::execute() {
    //Tenta executar a query
    if (!mysql_query(this->_conn,this->_queryString.c_str())) {
        this->_total_rows = (int) mysql_affected_rows(this->_conn);
        return true;
    } else {
        this->_total_rows = 0;
        return false;
    }
}

int VSQL_MYSQL::Statement::rowCount() {
    return this->_total_rows;
}

int VSQL_MYSQL::Statement::columnCount() {
    return this->_total_cols;
}

void VSQL_MYSQL::Statement::clearResultSet() {
    //Limpa o resultset
}