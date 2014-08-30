#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vin.h"
#include "web.h"

int main(int argc, char **argv) {
    wsInit();
    int fd;
    while (1) {
        fd = wsAccept();
        if (fd < -1) {
            printf("Error in accepting connection\n");
            exit(1);
        }

        HttpRequest *req = wsGetRequest(fd);
        char resp[256];
        sprintf(resp, "%s\n", HttpGetUri(req));
        printf("%s\n", HttpGetUri(req));
        wsSendResponse(fd, resp);
    }
    close(fd);
    return vvMain(argc, argv);
}
