#include <stdio.h>
#include <string.h>

#include "hashmap.h"

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
        fgets(def, sizeof(def), stdin);
        int len = strlen(def);
        if (len == sizeof(def)-1)  {
            //printf("Definition is too long, detected at %s, recovering\n", word);
            do {
                fgets(def, sizeof(def), stdin);
            } while (strlen(def) == sizeof(def)-1);
        }
        if (len > 1) {
            def[len-1] = 0;
            putValue(h, word, def);
        } else {
            //printf("No definition for %s, not saving\n", word);
        }
    }
    dumpHash(h, false);
    return 0;
}
