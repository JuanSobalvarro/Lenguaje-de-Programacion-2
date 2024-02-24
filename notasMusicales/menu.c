#include "menu.h"

static void freeMenu(MENU *menu)
{
    free(menu);
}

/*
    Allocate menu in memory
*/
MENU *createMenu(void(**ptrs)(), char **names, unsigned int size)
{
    MENU *menu = malloc(sizeof(MENU));

    menu->func_ptrs = ptrs;
    menu->func_names = names;
    menu->size = size;
}
/*
    Print menu and return the selected function
*/
static int printMenu(MENU *menu)
{
    printf("====================================================================\n");
    printf("\033[31;6;7mBienvenido al Gestor de Notas Musicales y Construcción de Acordes\033[0m\n");
    printf("====================================================================\n");

    printf("Selecciona una funcion: (1 - %d)\n\n", menu->size + 1);

    for (int i = 0; i < menu->size; i++)
    {
        printf("%d. %s\n", i+1, menu->func_names[i]);
    }
    printf("%d. Salir\n\n", menu->size + 1);

    int selection;

    printf("Seleccionando funcion: ");

    scanf("%d", &selection);

    //printf("%d\n", selection);

    if (selection < 0  || selection > menu->size+1)
    {
        printf("Seleccion no valida\n", selection);
        return -1;
    }
    return selection-1;
}

/*
    Create the menu loop
*/
void loopMenu(MENU *menu, NOTES *n)
{
    while (1)
    {
        int select = printMenu(menu);

        if (select == -1)
        {
            continue;
        }
        else if (select == menu->size)
        {
            printf("Exiting program\n");
            freeMenu(menu);
            return;
        }

        system("CLS");

        //printf("Executing %s\n\n", menu->func_names[select]);

        //printf("function pointer: %p\n", menu->func_ptrs[select]);

        (menu->func_ptrs[select])(n);

        
        printf("Exit program pressing any key\n");
        getchar();
        system("CLS");
    }
}

