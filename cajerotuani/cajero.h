#ifndef CAJERO_H
#define CAJERO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "../uwunya/utilities/utilities.h"

typedef struct tm local;

typedef struct ACCOUNT
{
    char id[5];
    char pin[5];
    char name[10];
    float balance;
} ACCOUNT;

typedef struct CAJERO
{
    ACCOUNT *account;
    int *bills; // quantity of each bills in the atm
    int *billsVal; // values of bills
    char *accountsPath; // csv path of accounts
    char *movementsPath; // csv path of movements
    char *tempPath;
} CAJERO;

CAJERO *initCAJERO(char *accPATH, char *movPATH, char *tempPath);

void *execCAJERO(CAJERO *caj);

#endif
