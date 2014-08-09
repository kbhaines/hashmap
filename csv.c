#include <stdlib.h>
#include <string.h>
#include "csv.h"

int32 splitCsv(char *input, char ***output) {

    char **results = malloc(MAX_RESULTS * sizeof(char*));
    int32 index = 0;
    char *startOfField = input;
    char this;
    do {
        this = *input++;
        if (this == ',' || this == 0) {
            int len = input - startOfField - 1;
            results[index++] = len > 0 ? strndup(startOfField, len) : NULL;
            startOfField = input;
        }
    } while (this != 0);
    *output = results;
    return index;
}

int32 splitCsvInPlace(char *input, char **output, int32 maxResults) {
    int32 index = 0;
    char *startOfField = input;
    char this;
    do {
        this = *input++;
        if (this == ',' || this == 0) {
            *(input - 1) = 0;
            output[index++] = startOfField;
            startOfField = input;
        }
    } while (this != 0 && index < maxResults);
    return index;
}
