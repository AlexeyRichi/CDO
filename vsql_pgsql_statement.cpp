#include "vsql_pgsql.h"
#include <boost/algorithm/string.hpp>

VSQL_PGSQL::Statement::Statement(std::string sql) {
    this->_queryString.append(sql);
}

void VSQL_PGSQL::Statement::bindParam(void* value, int data_type) {
    char * dado = new char[1000];
    if (data_type == PARAM_INT) {
        sprintf(dado,"%d",*((int *) value));
    } else if (data_type == PARAM_FLOAT) {
        sprintf(dado,"%f",*((float *) value));
    } else if (data_type == PARAM_STR) {
        sprintf(dado,"'%s'",(char *) value);
    }
    
    boost::replace_first(this->_queryString,"?",dado);
    printf("%s",this->_queryString.c_str());
    delete(dado);
}

