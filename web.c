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

struct HttpRequest {
    char *verb;
    char *uri;
};


const char *HttpGetVerb(const HttpRequest *req) {
    return req->verb;
}

const char *HttpGetUri(const HttpRequest *req) {
    return req->uri;
}

HttpRequest *HttpRequestFromString(const char *reqStr) {

    if (reqStr == NULL) {
        return NULL;
    }

    const int MAX_HTTP_FIELDS = 3;
    HttpRequest *result = malloc(sizeof(HttpRequest));
    char *req = strdup(reqStr);
    char *fields[MAX_HTTP_FIELDS+1];
    int32 nFields = splitByCharInPlace(req, fields, MAX_HTTP_FIELDS+1, ' ');
    if (nFields != 3) {
        return NULL;
    }

    result->verb = fields[0];
    result->uri = fields[1];
    return result;
}

void wsInit(void) {

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
    
    FILE *file = fdopen(fd, "r+");

    char line[256];
    fgets(line, sizeof(line), file);
    HttpRequest *result = HttpRequestFromString(line);
    return result;

    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        if (len < 2) {
            printf("Error: detected invalid line");
            exit(1);
        } else if (len == 2) {
            return result;
        }
        // strip off the CR/LF characters
        line[--len] = 0;
        line[--len] = 0;
        //result->requestLine = strdup(line);
        break;
    }
}

void wsSendResponse(int rsock, const char *response) {
    write(rsock, response, strlen(response));
    close(rsock);
}
