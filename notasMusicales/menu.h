#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdio.h>
#include "notes.h"

/*
    MENU is a menu where we select the function that
    we want to execute.
    USAGE: When creating a menu with createMenu() pass
    an array of adresses to the functions  
*/
typedef struct MENU
{
    void (**func_ptrs)();
    char **func_names;
    unsigned int size;
} MENU;

/*
    Creates a pointer to a menu after passing an array of functions adresses 
    functions = [f1, f2, f3] and their names = ["uwu", "uwunya", "lamama"]
    and the size = 3
*/
extern MENU *createMenu(void(**ptrs)(), char **func_names, unsigned int size);

extern void loopMenu(MENU *menu, NOTES *n);

#endif