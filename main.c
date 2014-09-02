#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vin.h"
#include "web.h"
#include "csv.h"
#include "hashmap.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <vinfile>\n", argv[0]);
        exit(0);
    }
    HashMap *vinHash = vvLoadHashMapFile(argv[1]);

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


        // Expecting request in format: /v1/vin/<vin> i.e. 4 fields separated
        // by '/'

        char *uri = strdup(HttpGetUri(req));
        char *fields[4];
        if (splitByCharInPlace(uri,fields,4, '/') == 4) {
            const char *vin = fields[3];
            printf("%s %s\n", HttpGetUri(req), vin);
            const VinVehicle *v = getValue(vinHash, vin);
            if (v) {
                sprintf(resp, "%s %s %s", vvGetMake(v), vvGetModel(v), vvGetYear(v));
            } else {
                sprintf(resp, "Error: %s not found", vin);
            }
        } else {
            sprintf(resp, "Error: %s", HttpGetUri(req));
        }
        free(uri);
        wsSendResponse(fd, resp);
        HttpFree(req);
    }
    close(fd);
}
