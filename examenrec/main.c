#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct MENU
{
    void(**func_ptrs)();
    char **func_names;
    unsigned int size;
} MENU;

MENU *createMenu(void(**ptrs)(), char **names, unsigned int size);
int printMenu(MENU *menu);
void loopMenu(MENU *menu, float *array, int size);

void printOp(float *array, int size, char op);

void sum(float *array, int size);
void sub(float *array, int size);
void mult(float *array, int size);
void divi(float *array, int size);
void power(float *array, int size);

int main()
{
    int n;
    char str[100];
    do
    {
        
        printf("Cuantos numeros quiere generar(mayor que 2)? \n");
        scanf("%s", str);
    } while(!sscanf(str, "%d", &n) || n < 2);
    

    float *array = malloc(n * sizeof(float));
    for (int i = 0; i < n; i++)
    {
        do
        {
            printf("Num %d: ", i+1);
            scanf("%s", str);
            
        } while (!sscanf(str, "%f", &array[i]));
        
        
        //printf("Num %d: %d\n", i, array[i]);
    }

    char *names[] = {"Suma", "Resta", "Multiplicacion", "Division", "Power"};
    void (*functions[])(float*, int) = {sum, sub, mult, divi, power};
    MENU *m = createMenu(functions, names, 5);   

    loopMenu(m, array, n);

    free(array);
    return 0;
}

MENU *createMenu(void(**ptrs)(), char **names, unsigned int size)
{
    MENU *menu = malloc(sizeof(MENU));

    menu->func_ptrs = ptrs;
    menu->func_names = names;
    menu->size = size;
}

int printMenu(MENU *menu)
{
    printf("====================================================================\n");
    printf("\033[31;6;7mWELCOME\033[93;6;7mBIENVENIDO\033[92;6;7mWILLKOMMEN\033[0m a menu de tareas/funciones/metodos/etc\n");
    printf("====================================================================\n");

    printf("Select a function: (1 - %d)\n\n", menu->size + 1);

    for (int i = 0; i < menu->size; i++)
    {
        printf("%d. %s\n", i+1, menu->func_names[i]);
    }
    printf("%d. Exit\n\n", menu->size + 1);

    int selection;

    printf("Selecting function: ");

    scanf("%d", &selection);

    //printf("%d\n", selection);

    if (selection < 0  || selection > 9)
    {
        printf("ERROR READING THE SELECTION: %d readed\n", selection);
        return menu->size;
    }
    return selection-1;
}

/*
    Create the menu loop
*/
void loopMenu(MENU *menu, float *array, int size)
{
    while (1)
    {
        int select = printMenu(menu);

        if (select == menu->size)
        {
            printf("Exiting program\n");
            return;
        }

        printf("selecting %d\n", select);
        getchar();

        system("CLS");

        printf("Executing %s\n\n", menu->func_names[select]);

        //printf("function pointer: %p\n", menu->func_ptrs[select]);

        (menu->func_ptrs[select])(array, size);

        
        printf("Exit program pressing any key\n");
        getchar();
        getchar();
        system("CLS");
    }
}

void printOp(float *array, int size, char op)
{
    for (int i = 0; i < size - 1; i++)
    {
        printf("%f %c ", array[i], op);
    }
    printf("%f = ", array[size-1]);
}

void sum(float *array, int size)
{
    printOp(array, size, '+');

    float op = 0;
    for (int i = 0; i < size; i++)
    {
        op += array[i];
    }

    printf("%f\n\nSuma realizada\n", op);
}
void sub(float *array, int size)
{
    printOp(array, size, '-');

    float op = array[0];
    for (int i = 1; i < size; i++)
    {
        op -= array[i];
    }

    printf("%f\n\nResta realizada\n", op);
}
void mult(float *array, int size)
{
    printOp(array, size, '*');

    float op = 1;
    for (int i = 0; i < size; i++)
    {
        op *= array[i];
    }

    printf("%f\n\nMultiplicacion realizada\n", op);
}
void divi(float *array, int size)
{
    printOp(array, size, '/');

    float op = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] == 0)
        {
            printf("Indefinido\nNo se puede dividir entre 0\n");
            return;
        }
        op /= array[i];
    }

    printf("%f\n\nDivision realizada\n", op);
}
void power(float *array, int size)
{
    printOp(array, size, '^');

    float op = array[0];
    for (int i = 1; i < size; i++)
    {
        if (op == 0 && array[i] == 0)
        {
            printf("Indeterminacion 0^0\n\n");
            return;
        }
        op = pow(op, array[i]);
    }

    printf("%f\n\nPotencia realizada de izquierda a derecha\n", op);
}
