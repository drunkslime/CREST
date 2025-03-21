#include <microhttpd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/utils.h"
#include "include/userHandler.h"

HTTP_Response user_handler (char * url, char * method) {
    
    char * url_str = (char * ) url;
    char * method_str = (char * ) method;
    HTTP_Response http_response;
    
    if (strcmp(url_str, "/users") == 0) {
        if (strcmp(method_str, "GET") == 0) {
            char * json_data = read_user_file("src/data/users.json");
            http_response = (HTTP_Response){
                .body = json_data,
                .status = OK
            };
        } else if (strcmp(method_str, "POST") == 0) {
            http_response = (HTTP_Response){
                .body = format_json_response("Not implemented"),
                .status = NOT_IMPLEMENTED
            };
        }
    } else {
        http_response = (HTTP_Response){
            .body = format_json_response("Not found"),
            .status = NOT_FOUND
        };
    }
    
    return http_response;
}