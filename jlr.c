#include <stdio.h>
#include <string.h>

#include "types.h"
#include "hashmap.h"

#include "csv.h"

int main(int argc, char **argv) {
    HashMap *h = newHashMap();

    char line[512];
    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        if (len == sizeof(line)-1)  {
            //printf("Definition is too long, detected at %s, recovering\n", word);
            do {
                fgets(line, sizeof(line), stdin);
            } while (strlen(line) == sizeof(line)-1);
        }
        line[len-1] = 0;
        char **split;
        int32 num = splitCsv(line, &split);
        int32 j;
        for (j=0; j < num; j++) {
            printf("%s / ", split[j]);
        }
        printf("\n");
    }
    //dumpHash(h, true);
    return 0;
}
