#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "hashmap.h"

#include "csv.h"

int main(int argc, char **argv) {
    HashMap *h = newHashMap();

    char line[512];
    char **split = malloc(MAX_RESULTS * sizeof(char*));
    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        if (len == sizeof(line)-1)  {
            //printf("Definition is too long, detected at %s, recovering\n", word);
            do {
                fgets(line, sizeof(line), stdin);
            } while (strlen(line) == sizeof(line)-1);
        }
        line[len-1] = 0;
        int32 num = splitCsvInPlace(line, split, MAX_RESULTS);
        if (num == 7) {
            char *globalVin = split[0];
            char *nasVin = split[1];
            char *make = split[2];
            char *model = split[3];
            char *year = split[4];
            char *country = split[5];
            char *recalls = split[6];

            //printf("%s %s %s\n", nasVin, model, recalls);
            putValue(h, nasVin, recalls != NULL ? strdup(recalls) : "");
        } else {
            printf("Incorrect format: %s\n", line);
        }
    }
    dumpHash(h, false);
    return 0;
}
