#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdio.h>

char *inputString(FILE* fp, size_t *lenofS);

int isNum(char *s);

void *copymemory(void *dest, const void *src, size_t count);

char **readCSV(FILE *f);

#endif