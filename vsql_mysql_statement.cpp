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

VSQL_MYSQL::Row VSQL_MYSQL::Statement::fetch() {

    int index_from, index_where;
    index_from = this->_queryString.find("from", 0, 1);
    index_where = this->_queryString.find("where", 0, 1);

    if (index_from == -1) {
        index_from = this->_queryString.find("FROM", 0, 1) + 4;
    } else {
        index_from = index_from + 5;
    }

    if (index_where == -1) {
        index_where = this->_queryString.find("where", 0, 1);
    }

    std::string table_name;
    if (index_where = ! -1) {
        table_name = this->_queryString.substr(index_from, index_where - index_from);
    } else {
        table_name = this->_queryString.substr(index_from);
    }
    
    printf("Table name: %s",table_name.c_str());
    printf("Length: %d",table_name.size());



    //this->_result_set = mysql_list_fields(this->_conn,this->_result_set->,NULL);
    //this->_field = mysql_fetch_field(this->_result_set);
    //printf("Really? %s\n",this->_field->table);
    //printf("Really? %s\n",this->_field->name);
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