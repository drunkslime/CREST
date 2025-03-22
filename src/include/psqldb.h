#ifndef PSQLDB_H
#define PSQLDB_H

#include <postgresql/libpq-fe.h>

PGconn * psql_connect();

void psql_disconnect(PGconn * conn);

#endif