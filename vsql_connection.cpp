#include "vsql_connection_mysql.h"

VSQLConnection::VSQLConnection(std::string str_connection, const int db_type) {
    this->str_conn = str_connection;
    this->db_type = db_type;
}

bool VSQLConnection::openConnection() {
    if (this->db_type == VSQLConnection::PGSQL_DB) {

    } else if (this->db_type == VSQLConnection::MYSQL_DB) {

    }
}


