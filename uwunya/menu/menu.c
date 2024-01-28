#include "menu.h"

static int addFunction(MENU *menu, void (*func_ptr)(), char *name)
{
    return 1;
}

static int freeMenu(MENU *menu)
{


}

/*
    Print menu and return the selected function
*/
static int printMenu(MENU *menu)
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

MENU *createMenu(void(**ptrs)(), char **names, unsigned int size)
{
    MENU *menu = malloc(sizeof(MENU));

    menu->func_ptrs = ptrs;
    menu->func_names = names;
    menu->size = size;
}

/*
    Create the menu loop
*/
void loopMenu(MENU *menu)
{
    while (1)
    {
        int select = printMenu(menu);

        if (select == menu->size)
        {
            printf("Exiting program\n");
            return;
        }

        system("CLS");

        printf("Executing %s\n\n", menu->func_names[select]);

        //printf("function pointer: %p\n", menu->func_ptrs[select]);

        (menu->func_ptrs[select])();

        
        printf("Exit program pressing any key\n");
        getchar();
        getchar();
        system("CLS");
    }
}

