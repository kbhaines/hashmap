#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

#include "http.h"

extern void wsInit(void);
extern int wsAccept(void);
extern HttpRequest *wsGetRequest(int fd);
extern void wsSendResponse(int fd, const char *response);

#endif
