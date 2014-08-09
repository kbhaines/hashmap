#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED

#include "types.h"

#define MAX_RESULTS 32

// returns number of items in the output[] array
extern int32 splitCsv(char *input, char ***output);

#endif
