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
    if (!mysql_query(this->_conn, this->_queryString.c_str())) {
        this->_total_rows = (int) mysql_affected_rows(this->_conn);
        this->_result_set = mysql_store_result(this->_conn);
        return true;
    } else {
        this->_total_rows = 0;
        return false;
    }
}

Row VSQL_MYSQL::Statement::fetch() {

    this->_field = mysql_fetch_field(this->_result_set);

    this->_total_rows = (int) this->_result_set->row_count;
    this->_total_cols = this->_result_set->field_count;

    this->_mysql_row = mysql_fetch_row(this->_result_set);
    int i;
    std::string column;
    for (i = 0; i < this->_total_cols; i++) {
        column.append(this->_field->name);
        this->_row[column] = this->_mysql_row[i];
        this->_field++;
        column.clear();
    }
    return this->_row;
}

ResultSet VSQL_MYSQL::Statement::fetchAll() {
    MYSQL_FIELD * field;
    this->_field = mysql_fetch_field(this->_result_set);
    this->_total_rows = (int) this->_result_set->row_count;
    this->_total_cols = this->_result_set->field_count;

    int i, total;
    total = 0;
    std::string column;

    while (this->_mysql_row = mysql_fetch_row(this->_result_set)) {

        field = this->_field;
        for (i = 0; i < this->_total_cols; i++) {
            column.append(field->name);
            this->_row[column] = this->_mysql_row[i];
            field++;
            column.clear();
        }
        this->_result[total] = this->_row;
        this->_row.clear();
        total++;
    }
    return this->_result;
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