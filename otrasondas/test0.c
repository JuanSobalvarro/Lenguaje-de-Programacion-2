#include <stdio.h>

#include "uwunya/menu/menu.h"

void f0();
void f1();
void f2();

int main()
{
    void (*functions[])() = {f0, f1, f2};
    char *names[] = {"UWU", "kaka", "kk"};

    //printf("%s\n", names[1]);

    //functions[1]();
    //printf("function pointer: %p\n", functions[1]);

    MENU *uwu = createMenu(functions, names, 3);

    //printf("function pointer: %p\n", uwu->func_ptrs[1]);

    loopMenu(uwu);

    printf("Exit program pressing any key");
    getchar();
    return 0;
}

void f0()
{
    printf("uwu\n");
}
void f1()
{
    printf("kaka\n");
}
void f2()
{
    printf("kk\n");
}
