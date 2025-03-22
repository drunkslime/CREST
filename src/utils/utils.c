#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/utils.h"

char* format_json_response(const char* text) {
    size_t len = snprintf(NULL, 0, "{\"response\": \"%s\"}", text) + 1;
    char* json = malloc(len);
    if (json) {
        snprintf(json, len, "{\"response\": \"%s\"}", text);
    }
    return json;
}

#ifdef WIN32
    #define realpath(N,R) _fullpath((R),(N),PATH_MAX)
#endif

char* read_user_file(const char* filename) {
    char *absolute_path = realpath(filename, NULL);

    if (!absolute_path) {
        fprintf(stderr, "Failed to resolve path: %s\n", filename);
        fprintf(stderr, "Absolute path: %s\n", absolute_path);
        perror(("Error resolving path"));
        return NULL;
    }

    FILE* file = fopen(absolute_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return NULL;
    }
    
    // set pointer position to the end of file to calculate its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    fseek(file, 0, SEEK_SET);
    
    // Allocate memory for the file content
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    // Read the file content
    size_t read_size = fread(buffer, 1, file_size, file);
    buffer[read_size] = '\0';  // Null-terminate the string
    
    fclose(file);
    return buffer;
}

char * get_time(void) {
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    char * fttime = asctime(ptr);
    fttime[strlen(fttime) - 6] = 0; // clear beginning
    fttime = fttime + 11; // clear ending
    return fttime;
}