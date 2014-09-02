#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

#include "csv.h"
#include "web.h"
#include "types.h"

static int sock;

void wsInit(void) {

    int port = 8080;
    int backlog = 200;

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
        printf("Error: Couldn't bind to port %d\n", port);
        exit(1);
    }

    listen(sock, backlog);
}


int wsAccept() {
    
    struct sockaddr_in client_addr;
    int client_len = sizeof(client_addr);
    int newsock = accept(sock, (struct sockaddr *) &client_addr, &client_len);

    return newsock;
}


HttpRequest *wsGetRequest(int fd) {
    return HttpRequestFromFd(fd);
}

void wsSendResponse(int rsock, const char *response) {
    char header[128];
    int len = sprintf(header,"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    write(rsock, header, len);
    write(rsock, response, strlen(response));
}
