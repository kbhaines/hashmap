#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "http.h"

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

HttpRequest *HttpRequestFromFd(int fd) {
    FILE *file = fdopen(fd, "r+");
    char line[256];
    fgets(line, sizeof(line), file);
    return HttpRequestFromString(line);
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

