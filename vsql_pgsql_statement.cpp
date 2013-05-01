#include "vsql_pgsql.h"
#include <libpq-fe.h>
#include <boost/algorithm/string.hpp>

VSQL_PGSQL::Statement::Statement(std::string sql, PGconn * conn) {
    this->_queryString.append(sql);
    this->_conn = conn;
}

void VSQL_PGSQL::Statement::bindParam(void* value, int data_type) {
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

void VSQL_PGSQL::Statement::bindValue(std::string param, void* value, int data_type) {
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

bool VSQL_PGSQL::Statement::execute() {
    //Tenta executar a query
    this->_result_set = PQexec(this->_conn, this->_queryString.c_str());

    if (PQresultStatus(this->_result_set) == PGRES_COMMAND_OK) {
        //Se entrar aqui a query rodou beleza
        this->clearResultSet();
        return true;
    } else if (PQresultStatus(this->_result_set) == PGRES_TUPLES_OK) {
        //Se entrar aqui a query rodou beleza
        this->clearResultSet();
        return true;
    } else {
        //Se entrar aqui  a query não rodou
        this->clearResultSet();
        return false;
    }
}

VSQL_PGSQL::Row VSQL_PGSQL::Statement::fetch() {

}

void* VSQL_PGSQL::Statement::fetchObject() {

}

VSQL_PGSQL::ResultSet VSQL_PGSQL::Statement::fetchAll() {

}

int VSQL_PGSQL::Statement::rowCount() {

}

void VSQL_PGSQL::Statement::clearResultSet() {
    //Limpa o resultset
    PQclear(this->_result_set);
}