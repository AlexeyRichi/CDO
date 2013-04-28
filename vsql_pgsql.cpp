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
}

bool VSQL_PGSQL::Connection::openConnection() {
    char * str_conn = new char[300];
    sprintf(str_conn, "host=%s user=%s password=%s port=%d dbname=%s", this->_host.c_str(), this->_user.c_str(),\
    this->_passwd.c_str(), this->_port, this->_dbname.c_str());
    
    //Abre a conexão agora.
    this->_conn = PQconnectdb(str_conn);
    delete(str_conn);
    
    if (PQstatus(this->_conn) != CONNECTION_OK) {
        return false;
    } else {
        return true;
    }
}

bool VSQL_PGSQL::Connection::beginTransaction() {
    
}

bool VSQL_PGSQL::Connection::exec(std::string sql) {
    this->_result_set = PQexec(this->_conn,sql.c_str());
    if (PQresultStatus(this->_result_set) == PGRES_COMMAND_OK) {
        this->clearResultSet();
        return true;
    } else if (PQresultStatus(this->_result_set) == PGRES_TUPLES_OK) {
        this->clearResultSet();
        return true;
    } else {
        this->clearResultSet();
        return false;
    }
}

std::string VSQL_PGSQL::Connection::getErrorMessage() {
    this->_error_message = PQerrorMessage(this->_conn);
    return this->_error_message;
}

void VSQL_PGSQL::Connection::clearResultSet() {
    PQclear(this->_result_set);
}

bool VSQL_PGSQL::Connection::closeConnection() {
    PQfinish(this->_conn);
    if (PQstatus(this->_conn) != CONNECTION_BAD) {
        return false;
    } else {
        return true;
    }
}




