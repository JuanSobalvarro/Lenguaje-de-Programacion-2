#include <stdio.h>

#include "cajero.h"

int main()
{ 
    CAJERO *caj = initCAJERO("cajerotuani/accounts.csv", "cajerotuani/movements.csv");

    execCAJERO(caj);

    return 0;
}