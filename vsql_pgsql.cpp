#include "vsql_pgsql.h"

VSQL_PGSQL::Connection::Connection(std::string host, std::string user, std::string passwd, std::string dbname, int port) {
    this->_host.append(host);
    this->_user.append(user);
    this->_passwd.append(passwd);
    this->_dbname.append(dbname);
    if (port != 5432) {
        this->_port = port;
    } else {
        this->_port = 5432;
    }
    char * str_conn = new char[300];
    sprintf(str_conn,"host=%s user=%s password=%s port=%d dbname=%s",this->_host.c_str(),this->_user.c_str(),\
    this->_passwd.c_str(),this->_port,this->_dbname.c_str());
}

bool VSQL_PGSQL::Connection::openConnection() {
    
}




