#include "vsql.h"

void set_database_type(int type) {
    if (type == PGSQL) {
        using namespace VSQL_PGSQL;
    } else if (type == MYSQL) {
        using namespace VSQL_MYSQL;
    } else if (type == SQLITE) {
        using namespace VSQL_SQLITE;
    }
}

void free_conn(VSQL_MYSQL::Connection* conn) {
    delete(conn);
}

void free_conn(VSQL_PGSQL::Connection* conn) {
    delete(conn);
}

void free_conn(VSQL_SQLITE::Connection* conn) {
    delete(conn);
}

void free_statement(VSQL_MYSQL::Statement* stm) {
    delete(stm);
}

void free_statement(VSQL_PGSQL::Statement* stm) {
    delete(stm);
}

void free_statement(VSQL_SQLITE::Statement* stm) {
    delete(stm);
}