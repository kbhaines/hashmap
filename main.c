#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vin.h"
#include "web.h"

int main(int argc, char **argv) {
    ws_init();
    int fd = ws_accept();
    if (fd < -1) {
        printf("Error in accepting connection\n");
        exit(1);
    }

    FILE *file = fdopen(fd, "r+");

    char line[256];
    char result[sizeof(line)];
    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        if (len) line[--len] = 0;
        if (len) line[--len] = 0;
        printf("%d %s\n",len, line);
        if (strlen(line) == 0) {
            break;
        }
        int j;
        //for (j=0;j<10;j++) printf("%hhd:%c ", line[j], (int)(line[j]));
        sprintf(result,"header: %s\r\n",line);
        //fputs(result, file);
        write(fd, result, strlen(result));
    }
    printf("continue");
    fclose(file);
    return vvMain(argc, argv);
}
