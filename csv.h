#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED

#include "types.h"

#define MAX_RESULTS 32

// returns number of items in the output[] array
extern int32 splitCsv(const char *input, char ***output);
static int32 splitByChar(const char *input, char ***output, char splitChar);

extern int32 splitCsvInPlace(char *input, char **output, int32 maxResults);
extern int32 splitByCharInPlace(char *input, char **output, int32 maxResults, char splitChar);

#endif
