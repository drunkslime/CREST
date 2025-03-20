#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#include "include/utils.h"

#define DEFPAGE "<html><body><form action=\'/hello\'><button type=\'submit\' method=\'POST\'>Click me</button></form></body></html>"
#define PAGE(s) "<html><body><h1>" s "</h1></body></html>"

static enum MHD_Result 
ahc_echo(
    void * cls,
    struct MHD_Connection * connection,
    const char * url,
    const char * method,
    const char * version,
    const char * upload_data, 
    size_t * upload_data_size, 
    void ** ptr) {
        
        char * url_str = (char * ) url;
        char * method_str = (char * ) method;
        int ret;

        struct MHD_Response * response;
        HTTP_Response http_response;

        if (strcmp(url_str, "/") == 0) {
            http_response = (HTTP_Response){
                .body = DEFPAGE,
                .status = OK
            };
        } else if (strcmp(url_str, "/hello") == 0) {
            if (strcmp(method_str, "POST") == 0) {
                http_response = (HTTP_Response){
                    .body = ("<script>console.log('Fuck You Bastard, You called", method_str, " method')</script>"),
                    .status = OK
                };
            } else {
                http_response = (HTTP_Response){
                    .body = PAGE("Hello"),
                    .status = OK
                };
            }
        } else if (strcmp(url_str, "/world") == 0) {
            http_response = (HTTP_Response){
                .body = PAGE("World"),
                .status = OK
            };  
        } else if (strcmp(url_str, "/users") == 0) {
            http_response = (HTTP_Response){
                .body = PAGE("World"),
                .status = OK
            };  
        } else {
            http_response = (HTTP_Response){
                .body = PAGE("Not Found"),
                .status = NOT_FOUND
            };
        }

        char * page = http_response.body;

        response = MHD_create_response_from_buffer(
            strlen(page), 
            (void* ) page, 
            MHD_RESPMEM_PERSISTENT
        );

        if (!response) return MHD_NO;

        ret = MHD_queue_response(
            connection,
            http_response.status,
            response
        );

        MHD_destroy_response(response);
        return ret;
    }