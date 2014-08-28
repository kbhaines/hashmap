#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

typedef struct HttpRequest HttpRequest;

extern void wsInit(void);

extern int wsAccept(void);

extern HttpRequest *wsGetRequest(int fd);

extern const char * HttpGetRequest(HttpRequest *req);

#endif
