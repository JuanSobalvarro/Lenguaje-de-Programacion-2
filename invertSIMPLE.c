#include <stdio.h>

int main()
{
    int num = -1;
    //printf("%d\n",__INT_MAX__);
    do
    {
        printf("Ingrese un numero entero no negativo menor de INT_MAX: ");
        if(!scanf("%d", &num))
        {
            while(getchar() != '\n');
        }
    } while(num < 10);
    
    printf("%d -> ", num);

    do
    {   
        printf("%d", num%10);
        num /= 10;
    } while (num != 0);
    
    printf("\nGG\n");
    return 0;
}