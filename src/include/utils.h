#ifndef UTILS_H
#define UTILS_H

typedef enum {
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501
} HTTP_Status;

typedef struct {
    char * body;
    HTTP_Status status;
} HTTP_Response;

char* read_user_file(const char* filename);

#endif