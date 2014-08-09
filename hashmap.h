#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED
typedef unsigned char uint8;
typedef int int32;
typedef unsigned int uint32;
typedef uint8 bool;
#define true 1
#define false 0


typedef struct HashMap HashMap;

extern HashMap *newHashMap(void);

extern char *getValue(HashMap *hm, char *key);

extern const char *putValue(HashMap *hm, const char *key, const char *value);

extern void dumpHash(HashMap *h, bool dumpContents);
#endif
