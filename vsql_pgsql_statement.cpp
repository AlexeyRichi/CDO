#include "vsql_pgsql.h"
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

    if (PQresultStatus(this->_result_set) != PGRES_COMMAND_OK) {
        this->_total_rows = 0;
        return false;
    } else if (PQresultStatus(this->_result_set) != PGRES_TUPLES_OK) {
        this->_total_rows = 0;
        return false;
    }
    this->_total_rows = PQntuples(this->_result_set);
    return true;
}

Row VSQL_PGSQL::Statement::fetch() {
    int colunas;
    colunas = PQnfields(this->_result_set);
    for (int i = 0; i < colunas; i++) {
        char * nome_coluna = PQfname(this->_result_set, i);
        this->_row[nome_coluna] = PQgetvalue(this->_result_set, 0, i);
    }
    this->_total_rows = 1;
    this->_total_cols = colunas;
    this->clearResultSet();
    return this->_row;
}

ResultSet VSQL_PGSQL::Statement::fetchAll() {
    int linhas, colunas;
    linhas = PQntuples(this->_result_set);
    colunas = PQnfields(this->_result_set);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            char * nome_coluna = PQfname(this->_result_set, j);
            this->_row[nome_coluna] = PQgetvalue(this->_result_set, i, j);
        }
        this->_result[i] = this->_row;
    }
    this->_total_rows = linhas;
    this->_total_cols = colunas;
    this->clearResultSet();
    return this->_result;
}

int VSQL_PGSQL::Statement::rowCount() {
    return this->_total_rows;
}

int VSQL_PGSQL::Statement::columnCount() {
    return this->_total_cols;
}

void VSQL_PGSQL::Statement::clearResultSet() {
    //Limpa o resultset
    PQclear(this->_result_set);
}