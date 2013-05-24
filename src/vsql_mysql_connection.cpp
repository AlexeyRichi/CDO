#include "vsql_mysql.h"

VSQL_MYSQL::Connection::Connection(std::string host, std::string user, std::string passwd, std::string dbname, int port) {
    this->_host.append(host);
    this->_user.append(user);
    this->_passwd.append(passwd);
    this->_dbname.append(dbname);
    if (port != 3306) {
        this->_port = port;
    } else {
        this->_port = 3306;
    }
}

bool VSQL_MYSQL::Connection::openConnection() {
    //Inicia o ponteiro
    this->_conn = mysql_init(NULL);

    //Tenta Conectar
    if (!mysql_real_connect(this->_conn, this->_host.c_str(), this->_user.c_str(), this->_passwd.c_str(), this->_dbname.c_str(), this->_port, NULL, 0)) {
        //Se falhar, grava a mensagem de erro
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    } else {
        return true;
    }

}

bool VSQL_MYSQL::Connection::beginTransaction() {
    //Tentando começar a transaction

    //Desliga o AutoCommit
    if (!mysql_autocommit(this->_conn, false)) {
        this->_error_message.clear();
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    }

    if (mysql_query(this->_conn, "BEGIN;")) {
        this->_error_message.clear();
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    } else {
        return true;
    }

}

bool VSQL_MYSQL::Connection::savePointTransaction(std::string savePointName) {
    char * sql = new char[200];
    sprintf(sql, "SAVEPOINT %s", savePointName.c_str());
    if (mysql_query(this->_conn, sql)) {
        this->_error_message.clear();
        this->_error_message.append(mysql_error(this->_conn));
        delete(sql);
        return false;
    } else {
        delete(sql);
        return true;
    }
}

bool VSQL_MYSQL::Connection::commitTransaction() {
    if (mysql_query(this->_conn, "COMMIT;")) {
        this->_error_message.clear();
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    } else {
        return true;
    }

}

bool VSQL_MYSQL::Connection::rollbackTransaction() {

    if (mysql_query(this->_conn, "ROLLBACK;")) {
        this->_error_message.clear();
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    } else {
        return true;
    }

}

bool VSQL_MYSQL::Connection::rollbackTransaction(std::string savepoint) {
    char * sql = new char[100];
    sprintf(sql, "rollback %s", savepoint.c_str());
    if (mysql_query(this->_conn, sql)) {
        this->_error_message.clear();
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    } else {
        return true;
    }

}

bool VSQL_MYSQL::Connection::exec(std::string sql) {
    if (mysql_query(this->_conn, sql.c_str())) {
        this->_error_message.clear();
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    } else {
        return true;
    }
}

VSQL_MYSQL::Statement * VSQL_MYSQL::Connection::prepare(std::string sql) {
    VSQL_MYSQL::Statement * stm;
    stm = new VSQL_MYSQL::Statement(sql, this->_conn);
    return stm;
}

VSQL_MYSQL::Statement * VSQL_MYSQL::Connection::query(std::string sql) {
    VSQL_MYSQL::Statement * stm;
    stm = new VSQL_MYSQL::Statement(sql, this->_conn);
    stm->execute();
    return stm;
}

std::string VSQL_MYSQL::Connection::getErrorMessage() {
    return this->_error_message;
}

bool VSQL_MYSQL::Connection::closeConnection() {
    mysql_close(this->_conn);
    return true;
}