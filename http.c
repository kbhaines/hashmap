#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "http.h"

struct HttpRequest {
    char *verb;
    char *uri;
    FILE *file;
};


const char *HttpGetVerb(const HttpRequest *req) {
    return req->verb;
}

const char *HttpGetUri(const HttpRequest *req) {
    return req->uri;
}

void HttpFree(HttpRequest *h) {
    if (h->file) {
        fclose(h->file);
    }
    free(h->verb);
    free(h);
}

HttpRequest *HttpRequestFromFd(int fd) {
    char line[256];
    FILE *file = fdopen(fd, "r+");
    if (file && fgets(line, sizeof(line), file)) {
        HttpRequest *result= HttpRequestFromString(line);
        result -> file = file;
        return result;
    }
    return NULL;
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
        free(req);
        return NULL;
    }

    result->verb = fields[0];
    result->uri = fields[1];
    result->file = NULL;
    return result;
}

