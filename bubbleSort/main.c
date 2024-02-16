#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void graph(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d: ", array[i]);
        for (int j = 0; j < array[i]; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void bubbleSort(int *array, int len)
{
    int step = 0;
    int comp = 0;
    for (int i = 1; i < len; i++)
    {
        for (int j = 0; j <= len - 2; j++)
        {
            comp++;
            // si es menor hacer swap
            if (array[j] > array[j+1])
            {   
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                printf("Paso %d: ", ++step);
                for (int k = 0; k < len; k++)
                {
                    if (k == j+1)
                    {
                        printf("\033[5;31m");
                    }
                    else if (k == j)
                    {
                        printf("\033[5;32m");
                    }
                    else
                    {
                        printf("\033[0m");
                    }
                    printf("%d ", array[k]);
                }
                printf("\033[0m");
                printf("\n");
            }   
        }
    }
    printf("\nMade %d comparisons\n", comp);
}

int main()
{
    int size;
    printf("Ingrese la cantidad de numeros a generar: ");
    scanf("%d", &size);
    int *nums = (int*) malloc(size * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        nums[i] = rand()%9 + 1;
    }

    printf("Before sorting\n");
    graph(nums, size);
    bubbleSort(nums, size);

    printf("\nAfter sorting\n");
    graph(nums, size);
    free(nums);
    return 0;
}