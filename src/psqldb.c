#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/psqldb.h"

PGconn * psql_connect() {
    PGconn *conn;
    conn = PQconnectdb("host=localhost port=5432 dbname=testdb user=postgres password=postgres");

    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Connected to database successfully\n");
    return conn;
}

void psql_disconnect(PGconn * conn) {
    fprintf(stdout, "Disconnecting from database\n");
    PQfinish(conn);
}