#include "vsql_sqlite.h"

int VSQL_SQLITE::Statement::rowCount() {
    return this->_total_rows;
}
