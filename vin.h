#ifndef VINVEHICLE_H_INCLUDED
#define VINVEHICLE_H_INCLUDED
#include "hashmap.h"
typedef struct VinVehicle VinVehicle;

extern const VinVehicle *vvGetFromCsv(const char *line);

extern const char *vvGetGlobalVin(const VinVehicle *vv);
extern const char *vvGetNasVin(const VinVehicle *vv);
extern const char *vvGetMake(const VinVehicle *vv);
extern const char *vvGetModel(const VinVehicle *vv);
extern const char *vvGetYear(const VinVehicle *vv);
extern const char *vvGetCountry(const VinVehicle *vv);
extern const char *vvGetRecalls(const VinVehicle *vv);

extern HashMap *vvLoadHashMapFile(const char *name);
extern HashMap *vvLoadHashMap(FILE *f);
#endif
