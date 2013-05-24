#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(VSQL, 0.1, vitor@softwaredevelopment.com.br)
AC_CONFIG_SRCDIR([/])
MYSQL_LIB=`mysql_config --libs`
echo $MYSQL_LIB
# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_YACC
AC_PROG_LN_S
# Checks for libraries.

#LibPQ
AC_CHECK_LIB([pq], [PQclear], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQgetvalue], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQfname], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQnfields], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQfinish], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQerrorMessage], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQresultStatus], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQexec], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQstatus], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQconnectdb], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

AC_CHECK_LIB([pq], [PQntuples], [],
[
	AC_MSG_ERROR([Could not find LibPQ library])
])

#MySQL

AC_CHECK_LIB([mysqlclient], [mysql_real_connect], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_init], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_error], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_autocommit], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_query], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_affected_rows], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_store_result], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_fetch_field], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_fetch_row], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_fetch_field], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_use_result], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])

AC_CHECK_LIB([mysqlclient], [mysql_free_result], [],
[
	AC_MSG_ERROR([Could not find MySQL library])
])


#SQLite
AC_CHECK_LIB([sqlite3], [sqlite3_open], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_exec], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_finalize], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_close], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_total_changes], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_errmsg], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_prepare], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_step], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])

AC_CHECK_LIB([sqlite3], [sqlite3_reset], [],
[
	AC_MSG_ERROR([Could not find SQLite library])
])


# Checks for header files.
#Headers padrão do C
AC_HEADER_STDC

AC_CHECK_HEADERS([postgresql/libpq-fe.h], [], 
[
	AC_CHECK_HEADERS([libpq-fe.h],[],[
		AC_MSG_ERROR([Could not find LibPQ headers])
	])
])

AC_CHECK_HEADERS([mysql/mysql.h], [], 
[
	AC_CHECK_HEADERS([mysql.h],[],[
		AC_MSG_ERROR([Could not find MySQL headers])
	])
])

AC_CHECK_HEADERS([sqlite3.h], [], 
[
	AC_MSG_ERROR([Could not find SQLite header])
])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([sqrt])
AC_OUTPUT(Makefile doc/Makefile man/Makefile script/Makefile src/Makefile)
