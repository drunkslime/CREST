#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

char* formatJSONResponse(const char* text) {
    size_t len = snprintf(NULL, 0, "{\"response\": \"%s\"}", text) + 1;
    char* json = malloc(len);
    if (json) {
        snprintf(json, len, "{\"response\": \"%s\"}", text);
    }
    return json;
}