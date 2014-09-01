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
        printf("0");
        fd = wsAccept();
        printf("a");
        if (fd < 0) {
            printf("Error in accepting connection\n");
            exit(1);
        }

        HttpRequest *req = wsGetRequest(fd);
        printf("g");
        if (!req) {
            printf("Error: couldn't parse request on %d\n", fd);
            continue;
        }
        char resp[256];
        printf("r");
        sprintf(resp, "%s\n", HttpGetUri(req));
        printf("%s\n", HttpGetUri(req));
        wsSendResponse(fd, resp);
        HttpFree(req);
    }
    close(fd);
    return vvMain(argc, argv);
}
