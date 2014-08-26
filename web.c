#include "web.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

void webserver(void) {

    int port = 8080;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        printf("Error: Couldn't create socket");
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
        printf("Error: Couldn't bind to port");
        exit(1);
    }
}

