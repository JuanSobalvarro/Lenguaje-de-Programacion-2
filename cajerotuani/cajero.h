#ifndef CAJERO_H
#define CAJERO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "C:/Clases/3.er Año/Primer Cuatrimestre/Lenguaje de Programacion 2/uwunya/utilities/utilities.h"

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
    int bills[4]; // quantity of each bills in the atm
    int billsVal[4]; // values of bills
    char *accountsPath; // csv path of accounts
    char *movementsPath; // csv path of movements
} CAJERO;

CAJERO *initCAJERO(char *accPATH, char *movPATH);

void *execCAJERO(CAJERO *caj);

#endif