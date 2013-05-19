#include "vsql.h"

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