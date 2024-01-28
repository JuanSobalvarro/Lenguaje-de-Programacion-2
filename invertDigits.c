#include <stdio.h>
#include <stdlib.h>

#include "uwunya/utilities/utilities.h"

int main()
{
    size_t digits;
    char *num;

    printf("Numero: ");
    num = inputString(stdin, &digits);

    if (!isNum(num))
    {
        printf("\nMust enter a valid real number\n");
        return -1;
    }

    //printf("Using number: %s\n", num);

    //printf("Digits = %d", digits);

    printf("%s -> ", num);
    for (int i = 0; i < digits; i++)
    {
        printf("%c", num[digits-i-1]);
    }
    
    printf("\nFINISHED\n");
    return 0;
}