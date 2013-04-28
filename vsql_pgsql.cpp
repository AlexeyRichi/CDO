
#include <libpq-fe.h>

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
    //Cria a string de conexão
    char * str_conn = new char[300];
    sprintf(str_conn, "host=%s user=%s password=%s port=%d dbname=%s", this->_host.c_str(), this->_user.c_str(),\
    this->_passwd.c_str(), this->_port, this->_dbname.c_str());

    //Abre a conexão agora.
    this->_conn = PQconnectdb(str_conn);
    delete(str_conn);

    //Verifica a conexão se foi aberta com sucesso
    if (PQstatus(this->_conn) != CONNECTION_OK) {
        this->closeConnection();
        return false;
    } else {
        return true;
    }
}

bool VSQL_PGSQL::Connection::beginTransaction() {
    //Começa a transaction
    this->_result_set = PQexec(this->_conn, "begin transaction");
    
    if (PQresultStatus(this->_result_set) == PGRES_COMMAND_OK) {
        //Se entrar aqui é porque a abertura da transaction funfou
        this->clearResultSet();
        return true;
    } else if (PQresultStatus(this->_result_set) == PGRES_TUPLES_OK) {
        //Se entrar aqui é porque a abertura da transaction funfou
        this->clearResultSet();
        return true;
    } else {
        //Se entrar aqui é porque a abertura da transaction não funfou
        this->clearResultSet();
        return false;
    }
}

bool VSQL_PGSQL::Connection::commit() {
    //Tenta dar o commit na transaction
    this->_result_set = PQexec(this->_conn, "commit transaction");
    
    if (PQresultStatus(this->_result_set) == PGRES_COMMAND_OK) {
        //Se entrar aqui, o comando de commit deu certo
        this->clearResultSet();
        return true;
    } else if (PQresultStatus(this->_result_set) == PGRES_TUPLES_OK) {
        //Se entrar aqui, o comando de commit deu certo
        this->clearResultSet();
        return true;
    } else {
        //Se entrar aqui, o comando de commit não deu certo
        this->clearResultSet();
        return false;
    }
}

bool VSQL_PGSQL::Connection::rollBack() {
    //Tenta dar o rollback na transaction
    this->_result_set = PQexec(this->_conn, "rollback transaction");
    
    if (PQresultStatus(this->_result_set) == PGRES_COMMAND_OK) {
        //Se entrar aqui o rollback aconteceu com sucesso
        this->clearResultSet();
        return true;
    } else if (PQresultStatus(this->_result_set) == PGRES_TUPLES_OK) {
        //Se entrar aqui o rollback aconteceu com sucesso
        this->clearResultSet();
        return true;
    } else {
        //Se entrar aqui o rollback falhou miseravelmente.
        this->clearResultSet();
        return false;
    }
}

bool VSQL_PGSQL::Connection::exec(std::string sql) {
    //Tetnta executar a query
    this->_result_set = PQexec(this->_conn, sql.c_str());
    
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

VSQL_PGSQL::Statement VSQL_PGSQL::Connection::query(std::string sql) {
    
}

std::string VSQL_PGSQL::Connection::getErrorMessage() {
    //Pega a ultima mensagem de erro e retorna
    this->_error_message = PQerrorMessage(this->_conn);
    return this->_error_message;
}

void VSQL_PGSQL::Connection::clearResultSet() {
    //Limpa o resultset
    PQclear(this->_result_set);
}

bool VSQL_PGSQL::Connection::closeConnection() {
    //Tenta fechar a conexão
    PQfinish(this->_conn);
    if (PQstatus(this->_conn) != CONNECTION_BAD) {
        return false;
    } else {
        return true;
    }
}