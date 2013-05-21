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

Row VSQL_SQLITE::Statement::fetch() {
    std::string nome_coluna;
    if (this->_total_rows == 0) {
        sqlite3_reset(this->_result_set);
        int i = 0;
        this->_total_cols = sqlite3_column_count(this->_result_set);
        sqlite3_step(this->_result_set);
        while (i<1) {
            for (i = 0; i<this->_total_cols; i++) {
                nome_coluna.append(sqlite3_column_name(this->_result_set, i));
                this->_row[nome_coluna].append((const char *) sqlite3_column_text(this->_result_set, i));
                nome_coluna.clear();
            }
        }
    }
    this->clearResultSet();
    return this->_row;
}

ResultSet VSQL_SQLITE::Statement::fetchAll() {
    std::string nome_coluna;
    int linhas = 0;
    if (this->_total_rows == 0) {
        sqlite3_reset(this->_result_set);
        int i = 0;
        this->_total_cols = sqlite3_column_count(this->_result_set);
        
        while (sqlite3_step(this->_result_set) == SQLITE_ROW) {
            for (i = 0; i<this->_total_cols; i++) {
                nome_coluna.append(sqlite3_column_name(this->_result_set, i));
                this->_row[nome_coluna].append((const char *) sqlite3_column_text(this->_result_set, i));
                nome_coluna.clear();
            }
            this->_result[linhas] = this->_row;
            linhas++;
            //Limpa a row
            this->_row.clear();
        }
    }
    //Totaliza as linhas afetadas
    this->_total_rows = linhas;
    this->clearResultSet();
    return this->_result;
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
