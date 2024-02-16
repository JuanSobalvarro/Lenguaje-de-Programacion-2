#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int *pointer;
    int size;

    srand(time(NULL));
    size = rand()%100 + 1;

    pointer = (int *) malloc(size * sizeof(int));

    if (pointer == NULL)
    {
        printf("ERROR::MAIN NO SE PUDO ALLOCALIZAR MEMORIA\n");
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        pointer[i] = i * 2;
    }

}