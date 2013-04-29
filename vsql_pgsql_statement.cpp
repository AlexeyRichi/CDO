#include "vsql_pgsql.h"

VSQL_PGSQL::Statement::Statement(std::string sql) {
    this->_queryString.append(sql);
}

void VSQL_PGSQL::Statement::bindParam(int param, void* value, int data_type) {

}

