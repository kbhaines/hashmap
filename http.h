#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

typedef struct HttpRequest HttpRequest;

extern HttpRequest *HttpRequestFromFd(int fd);
extern HttpRequest *HttpRequestFromString(const char *reqStr);

extern const char *HttpGetUri(const HttpRequest *req);
extern const char *HttpGetVerb(const HttpRequest *req);

#endif
