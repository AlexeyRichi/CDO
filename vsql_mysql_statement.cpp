#include "vsql_mysql.h"
#include <boost/algorithm/string.hpp>
#include <mysql/mysql.h>

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
    if (!mysql_query(this->_conn, this->_queryString.c_str())) {
        this->_total_rows = (int) mysql_affected_rows(this->_conn);
        this->_result_set = mysql_use_result(this->_conn);
        return true;
    } else {
        this->_total_rows = 0;
        return false;
    }
}

VSQL_MYSQL::Row VSQL_MYSQL::Statement::fetch() {

    this->_field = mysql_fetch_field(this->_result_set);

    this->_total_rows = (int) this->_result_set->row_count;
    this->_total_cols = this->_result_set->field_count;
    int columns = this->_total_cols;
    printf("Total Rows: %d\n", this->_total_rows);

    while (this->_mysql_row = mysql_fetch_row(this->_result_set)) {
        printf("valor: %s\n", this->_mysql_row[0]);
    }

    return this->_row;
}

VSQL_MYSQL::ResultSet VSQL_MYSQL::Statement::fetchAll() {

}

int VSQL_MYSQL::Statement::rowCount() {
    return this->_total_rows;
}

int VSQL_MYSQL::Statement::columnCount() {
    return this->_total_cols;
}

void VSQL_MYSQL::Statement::clearResultSet() {
    mysql_free_result(this->_result_set);
}