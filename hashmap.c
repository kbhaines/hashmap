#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashmap.h"

typedef struct KeyVal KeyVal;

struct KeyVal {
    const char *key;
    const char *value;
    KeyVal *next;
};


#define MAX_BUCKETS 1024
typedef struct HashMap {
    KeyVal *buckets[MAX_BUCKETS];
    uint32 (*hashFunc)(const char *);
    uint32 numItems;
} HashMap;

static KeyVal *findKeyVal(const HashMap *hm, const char *key) {
    KeyVal *kv = hm->buckets[hm->hashFunc(key)];
    while (kv) {
       if (strcmp(kv->key, key) == 0) {
           return kv;
       }
       kv = kv -> next;
    }
    return NULL;
}

static uint32 hashFunction2(const char *key) {

    uint32 hash = 0;
    int j, len = strlen(key);
    for (j = 0; j < len; j++ ) {
       hash += key[j]*j*102019;
    }
    return hash % MAX_BUCKETS;
}

static uint32 hashFunction3(const char *key) {
    uint32 hash = 5381;
    int c;
    while ( c = *key++ ) {
        hash = ((hash << 5) + hash + c);
    }
    return hash % MAX_BUCKETS;
}
        
static uint32 hashFunction1(const char *key) {
    return key[0]-32;
}


void dumpHash(HashMap *h, bool dumpContents) {

    uint32 b;
    uint32 deviation = 0;
    uint32 idealAverageItems = h->numItems/MAX_BUCKETS;
    for (b = 0; b < MAX_BUCKETS; b++) {
       if (h->buckets[b] != NULL) {
           KeyVal *kv = h->buckets[b];
           if (dumpContents)  {
               while (kv != NULL) {
                   printf("%d ", b);
                   printf("%s:%s \n", kv->key, kv->value);
                   kv = kv->next;
               }
           } else {
               int count = 0;
               while (kv != NULL) {
                   count ++;
                   kv = kv -> next;
               }
               //printf("%d items", count);
               deviation += abs(count - idealAverageItems);
           }
           //printf("\n");
       }
    }
   printf("\nItems: %d  Deviation: %d  Ideal: %d\n", h->numItems, deviation/MAX_BUCKETS, idealAverageItems);
}

const char *putValue(HashMap *hm, const char *key, const char *value) {

    int idx = hm->hashFunc(key);
    if (idx >= MAX_BUCKETS) {
       return NULL;
    }

    KeyVal *updateKv = findKeyVal(hm, key);
    if (updateKv) {
       updateKv -> value = strdup(value);
       return key;
    }

    KeyVal *oldHeadKv = hm->buckets[idx];
    KeyVal *newKv = malloc(sizeof(KeyVal));
    newKv->key = strdup(key);
    newKv->value = (value);
    newKv->next  = oldHeadKv;
    hm->buckets[idx] = newKv;
    hm->numItems++;
    return key;
}


const char *getValue(HashMap *hm, char *key) {
    KeyVal *kv = findKeyVal(hm, key);
    if (kv) {
       return kv -> value;
    }
    return NULL;
}

HashMap *newHashMap(void) {
    HashMap *h = malloc(sizeof(HashMap));
    int j;
    for (j = 0; j < MAX_BUCKETS; j++)
       h->buckets[j] = NULL;
    h->hashFunc = hashFunction3;
    return h;
}

