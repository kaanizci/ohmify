#include <stdio.h>
#include <time.h>
#include "utils.h"

void save_to_file(const char *result) {
    FILE *file = fopen("output.txt", "a");
    if (file == NULL) {
        printf("Could not open output.txt for writing.\n");
        return;
    }
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(file, "[%04d-%02d-%02d %02d:%02d] %s\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, result);
    fclose(file);
}