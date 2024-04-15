#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void *copyMem(void *dest, const void *source, int len);
int strtoint(char *str, int size);
char *getString(int *size);
int getInt();
int compStr(char *str1, char *str2);


#endif