#include <microhttpd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PAGE    "<html><head><title>CREST</title></head>"\
                "<body><h1>CREST</h1></body></html>"

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
        static int dummy;
        const char * page = cls;
        struct MHD_Response * response;
        int ret;

        if (0 != strcmp(method, "GET")) return MHD_NO; /* only GET allowed */
        if (&dummy != *ptr) {
            /* The first time only the headers are valid,
            do not respond in the first round...*/
            *ptr = &dummy;
            return MHD_YES;
        }
        if (0 != *upload_data_size) return MHD_NO; /* upload data in GET!? */
        *ptr = NULL; /* clear context pointer */
        response = MHD_create_response_from_buffer(
            strlen(page), 
            (void* ) page, 
            MHD_RESPMEM_PERSISTENT
        );
        ret = MHD_queue_response(
            connection,
            MHD_HTTP_OK,
            response
        );
        MHD_destroy_response(response);
        return ret;
    }

int main(int argc, char **argv) {
    struct MHD_Daemon * daemon;
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }
    daemon = MHD_start_daemon( /* Start a server daemon */
        MHD_USE_THREAD_PER_CONNECTION,
        atoi(argv[1]),
        NULL,
        NULL,
        &ahc_echo,
        PAGE,
        MHD_OPTION_END
    );

    if (daemon == NULL) return 1; /* error */
    (void) getc (stdin); /* wait for <CTRL-C>*/
    MHD_stop_daemon(daemon);
    return 0;
}


