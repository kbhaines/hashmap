#include "web.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

static int sock;

void ws_init(void) {

    int port = 8080;
    int backlog = 5;

    sock = socket(AF_INET, SOCK_STREAM, 0);

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

    listen(sock, backlog);
}


int ws_accept() {
    
    struct sockaddr_in client_addr;
    int client_len = sizeof(client_addr);
    int newsock = accept(sock, (struct sockaddr *) &client_addr, &client_len);

    return newsock;
}
