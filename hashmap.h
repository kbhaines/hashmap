#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED

#include "types.h"

typedef struct HashMap HashMap;

extern HashMap *newHashMap(void);

extern const char *getValue(HashMap *hm, char *key);

extern const char *putValue(HashMap *hm, const char *key, const char *value);

extern void dumpHash(HashMap *h, bool dumpContents);
#endif
