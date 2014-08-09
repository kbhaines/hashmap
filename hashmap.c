#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

typedef struct KeyVal KeyVal;

struct KeyVal {
    char *key;
    char *value;
    KeyVal *next;
};


#define MAX_BUCKETS 1024
typedef struct HashMap {
    KeyVal *buckets[MAX_BUCKETS];
    uint32 (*hashFunc)(const char *);
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
       hash += key[j];
    }
    return hash % MAX_BUCKETS;
}


static uint32 hashFunction1(const char *key) {
    return key[0]-32;
}


void dumpHash(HashMap *h, bool dumpContents) {

    uint32 b;
    for (b = 0; b < MAX_BUCKETS; b++) {
    
       if (h->buckets[b] != NULL) {
           printf("%d ", b);
           KeyVal *kv = h->buckets[b];
           if (dumpContents)  {
               while (kv != NULL) {
                   printf("%s:%s ", kv->key, kv->value);
                   kv = kv->next;
               }
           } else {
               int count = 0;
               while (kv != NULL) {
                   count ++;
                   kv = kv -> next;
               }
               printf("%d items", count);
           }
           printf("\n");
       }
    }

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
    newKv->value = strdup(value);
    newKv->next  = oldHeadKv;
    hm->buckets[idx] = newKv;
    return key;
}


char *getValue(HashMap *hm, char *key) {
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
    h->hashFunc = hashFunction2;
    return h;
}

