#include <stdio.h>

#include "cajero.h"

int main()
{ 
    CAJERO *caj = initCAJERO("cajerotuani/accounts.csv", "cajerotuani/movements.csv");

    if (caj == NULL)
    {
        printf("ERROR: COULDNT LOAD CAJERO");
        return -1;
    }

    return 0;
}