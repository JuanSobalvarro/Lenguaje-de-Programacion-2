#ifndef CAJERO_H
#define CAJERO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "C:/Clases/3.er Año/Primer Cuatrimestre/Lenguaje de Programacion 2/uwunya/utilities/utilities.h"

typedef struct ACCOUNT
{
    char id[4];
    char pin[4];
    char name[10];
    float balance;
} ACCOUNT;

typedef struct CAJERO
{
    ACCOUNT *account;
    int bills[4];
    int billsval[4];
} CAJERO;

/*
    Get accounts from a csv file and 
    returns an array of ACCOUNT pointers
*/
ACCOUNT **getACCOUNTS(FILE *fp, int *numAccounts)
{
    ACCOUNT **array;
    int arrlen = 0;
    char buffer[100];
    char *data;

    array = realloc(NULL, sizeof(ACCOUNT**) * arrlen);

    // get token headers
    fgets(buffer, sizeof(buffer), fp);
    printf("Accounts csv opened with headers: %s\n", buffer);
    for (int i = 0; feof(fp); i++)
    {
        ACCOUNT *a = malloc(sizeof(ACCOUNT));
        fgets(buffer, sizeof(buffer), fp);
        
        data = strtok(buffer, ",");
        copymemory(a->id, data, 4);

        data = strtok(NULL, ",");
        copymemory(a->pin, data, 4);

        data = strtok(NULL, ",");
        copymemory(a->name, data, sizeof(data));

        data = strtok(NULL, ",");
        a->balance = strtof(data, NULL);

        array[arrlen++] = a;
        array = realloc(NULL, sizeof(ACCOUNT**) * arrlen);
    }

    *numAccounts = arrlen;

    return array;
}

CAJERO *initCAJERO(char *accPATH, char *movPATH)
{
    CAJERO *c;
    c = malloc(sizeof(CAJERO));

    FILE *accf = fopen(accPATH, "r");
    if (accf == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE at %s\n", accPATH);
        return NULL;
    }

    FILE *movf = fopen(movPATH, "r");
    if (movf == NULL)
    {
        printf("ERROR: COULDNT OPEN FILE at %s\n", movPATH);
        return NULL;
    }

    int accSize;
    ACCOUNT **array = getACCOUNTS(accf, &accSize);

    if (array == NULL)
    {
        printf("ERROR: COULDNT LOAD ACCOUNTS ARRAY OR THERE IS NO ACCOUNTS REGISTER\n");
    }

    return c;
}

#endif