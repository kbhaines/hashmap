#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyVal KeyVal;
typedef unsigned char uint8;
typedef int int32;
typedef unsigned int uint32;
typedef uint8 bool;
#define true 1
#define false 0

struct KeyVal {
    char *key;
    char *value;
    KeyVal *next;
};


#define MAX_BUCKETS 1024
typedef struct {
    KeyVal *buckets[MAX_BUCKETS];
    uint32 (*func)(const char *);
} HashMap;

static KeyVal *findKeyVal(const HashMap *hm, const char *key) {
    KeyVal *kv = hm->buckets[hm->func(key)];
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


static void dumpHash(HashMap *h, bool dumpContents) {

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

    int idx = hm->func(key);
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
    h->func = hashFunction2;
    return h;
}

void test(HashMap *h) {
      char *names[][2] = { { "Kevin", "Haines" }, 
              { "Marcelle", "Haines" },
              { "Loen", "Miles" },
              { "Kev", "Miles" },
              { "Steve", "Wilson"}, 
              { NULL, NULL }
      };

      char *(*name)[2];
      for (name = names; (*name)[0] != NULL; name++) {
              printf("Adding %s:%s\n", (*name)[0], (*name)[1]);
              putValue(h, (*name)[0], (*name)[1]);
      }
      dumpHash(h, true);
      putValue(h,"Kevin","Miles");

      printf("\nUpdate\n");
      dumpHash(h, true);
}

int main(int argc, char **argv) {
      HashMap *h = newHashMap();
      //test(h);

      char word[16];
      char def[512] = "test";
      while (scanf("%s", word) > 0) {
              if (fgets(def, sizeof(def), stdin) != NULL){
                  int len = strlen(def);
                  printf("%s %d\n", word, len);
                  if (len > 0) {
                      def[len-1] = 0;
                      putValue(h, word, def);
                  } else {
                      printf("Discard %s ", word);
                  }
              } else {
                  printf("Discard %s ", word);
              }
               
      }
      dumpHash(h, false);
}


