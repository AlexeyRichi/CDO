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
    this->_conn = mysql_init(NULL);
    if (!mysql_real_connect(this->_conn, this->_host.c_str(), this->_user.c_str(), this->_passwd.c_str(), this->_dbname.c_str(), this->_port, NULL, 0)) {
        this->_error_message.append(mysql_error(this->_conn));
        return false;
    } else {
        return true;
    }

}