#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#include "include/utils.h"

static enum MHD_Result
default_handler(
    void *cls,
    struct MHD_Connection *connection,
    const char *url,
    const char *method,
    const char *version,
    const char *upload_data,
    size_t *upload_data_size,
    void **ptr)
{

    char *url_str = (char *)url;
    char *method_str = (char *)method;
    int ret;

    struct MHD_Response *response;
    HTTP_Response http_response;

    if (strcmp(url_str, "/") == 0) {
        http_response = (HTTP_Response){
            .body = format_json_response("Index"),
            .status = OK};
    }
    else if (strcmp(url_str, "/users") == 0) {
        http_response = user_handler(url_str, method_str);
    }
    else
    {
        http_response = (HTTP_Response){
            .body = format_json_response("Not found"),
            .status = NOT_FOUND};
    }

    char *page = http_response.body;

    response = MHD_create_response_from_buffer(
        strlen(page),
        (void *)page,
        MHD_RESPMEM_PERSISTENT);

    if (!response)
        return MHD_NO;

    // CORS headers
    MHD_add_response_header(response, "Access-Control-Allow-Origin", "*");
    MHD_add_response_header(response, "Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    MHD_add_response_header(response, "Access-Control-Allow-Headers", "Content-Type");

    MHD_add_response_header(response, "Content-Type", "application/json");

    ret = MHD_queue_response(
        connection,
        http_response.status,
        response);

    MHD_destroy_response(response);
    return ret;
}