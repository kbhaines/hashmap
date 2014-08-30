#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

typedef struct HttpRequest HttpRequest;

extern HttpRequest *HttpRequestFromString(const char *reqStr);
extern const char *HttpGetUri(const HttpRequest *req);
extern const char *HttpGetVerb(const HttpRequest *req);

extern void wsInit(void);

extern int wsAccept(void);

extern HttpRequest *wsGetRequest(int fd);

#endif
