#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "hashmap.h"

#include "csv.h"
#include "vin.h"


struct VinVehicle {
    char *globalVin;
    char *nasVin; 
    char *make; 
    char *model;
    char *year;
    char *country;
    char *recalls;
};

const VinVehicle *vvGetFromCsv(const char *line) {

    const int32 maxCsv = 7;
    char *split[maxCsv];
    int32 num = splitCsvInPlace(strdup(line), split, maxCsv);
    if (num == maxCsv) {
        VinVehicle *v = malloc(sizeof(VinVehicle));
        v->globalVin = split[0];
        v->nasVin = split[1];
        v->make = split[2];
        v->model = split[3];
        v->year = split[4];
        v->country = split[5];
        v->recalls = split[6] != NULL ? split[6] : "";
        return v;
    } else {
        return NULL;
    }
}

const char *vvGetGlobalVin(const VinVehicle *vv) {
    return vv->globalVin;
}

const char *vvGetNasVin(const VinVehicle *vv) {
    return vv->nasVin;
}

const char *vvGetMake(const VinVehicle *vv) {
    return vv->make;
}

const char *vvGetModel(const VinVehicle *vv) {
    return vv->model;
}

const char *vvGetYear(const VinVehicle *vv) {
    return vv->year;
}

const char *vvGetCountry(const VinVehicle *vv) {
    return vv->country;
}

const char *vvGetRecalls(const VinVehicle *vv) {
    return vv->recalls;
}


HashMap *vvLoadHashMap(FILE *f) {
    HashMap *h = newHashMap();
    char line[512];

    while (fgets(line, sizeof(line), f)) {
        int len = strlen(line);
        if (len == sizeof(line)-1)  {
            //printf("Definition is too long, detected at %s, recovering\n", word);
            do {
                fgets(line, sizeof(line), f);
            } while (strlen(line) == sizeof(line)-1);
        }
        line[len-1] = 0;
        const VinVehicle *v = vvGetFromCsv(line);
        if (v) {
            putValue(h, v->nasVin, v);
        } else {
            printf("Incorrect format: %s\n", line);
        }
    }
    return h;
}

HashMap *vvLoadHashMapFile(const char *name) {
    FILE *in = fopen(name,"r");
    if (!in) {
        printf("Error opening %s\n", name);
        exit(1);
    }
    return vvLoadHashMap(in);
}

int vvMain(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <vinfile>\n", argv[0]);
        exit(0);
    }
    HashMap *h = vvLoadHashMapFile(argv[1]);
    dumpHash(h, false);
    return 0;
}
