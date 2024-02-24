#include <stdio.h>
#include "notes.h"
#include "menu.h"

int main()
{
    NOTES *n = initializeNotes();

    if (n == NULL)
    {printf("reallocating after erasing with new N %d and first cahr %c\n", n->nCurrentNotes, *n->currentNotes);
        printf("Couldnt initialize notes\n");
    }
    
    MENU *menu = createMenu(n->functions, n->functionNames, n->functionsNumber);

    // loop menu already has memory free function
    loopMenu(menu, n);
    free(n);
    return 0;
}