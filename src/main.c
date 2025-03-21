#include <microhttpd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "handlers/handler.c"
#include "handlers/userHandler.c"

int main(int argc, char **argv)
{
    struct MHD_Daemon *daemon;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    daemon = MHD_start_daemon( /* Start a server daemon */
        MHD_USE_THREAD_PER_CONNECTION,
        atoi(argv[1]),
        NULL,
        NULL,
        &default_handler,
        NULL,
        MHD_OPTION_END
    );

    if (daemon == NULL) return 1;      /* error */

    (void)getc(stdin); /* wait for <CTRL-C>*/
    MHD_stop_daemon(daemon);
    return 0;
}
