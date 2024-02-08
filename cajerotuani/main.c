#include <stdio.h>

#include "cajero.h"

int main()
{ 
    CAJERO *caj = initCAJERO("cajerotuani/accounts.csv", "cajerotuani/movements.csv", "cajerotuani/temp.csv");

    execCAJERO(caj);

    return 0;
}