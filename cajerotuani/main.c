#include <stdio.h>

#include "cajero.h"

int main()
{ 
    CAJERO *caj = initCAJERO("cajerotuani/accounts.csv", "cajerotuani/movements.csv");

    execCAJERO(caj);

    float kk = caj->account->balance;

    printf("kk : %f\n", kk);

    return 0;
}