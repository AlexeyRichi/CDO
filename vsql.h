/* 
 * File:   vsql.h
 * Author: vitor
 *
 * Created on May 18, 2013, 10:55 PM
 */

#ifndef VSQL_H
#define	VSQL_H
#include "vsql_mysql.h"
#include "vsql_pgsql.h"
#include "vsql_sqlite.h"
#define PGSQL 0
#define MYSQL 1
#define SQLITE 2

void set_database_type(int type);

//Sqlite
void free_conn(VSQL_SQLITE::Connection * conn);

//Mysql
void free_conn(VSQL_MYSQL::Connection * conn);

//Pgsql
void free_conn(VSQL_PGSQL::Connection * conn);

//Sqlite
void free_statement(VSQL_SQLITE::Statement * stm);

//Mysql
void free_statement(VSQL_MYSQL::Statement * stm);

//Pgsql
void free_statement(VSQL_PGSQL::Statement * stm);

#endif	/* VSQL_H */

