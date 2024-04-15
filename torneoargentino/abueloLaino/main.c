#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char hasI(char *str);
void generateWord(char *word);

int main()
{
    srand(time(NULL));
    int timeIn, timeOut;
    double prom;
    for (int i = 0; i < 100; i++)
    {
        char word[20];
        generateWord(word);
        timeIn = time(NULL);
        char response = hasI(word);
        timeOut = time(NULL);
        printf("Palabra %d: %s\nResponse: %c\n", i+1, word, response);
        prom += (timeIn-timeOut)/100;
    }
    printf("Tiempo promedio por palabra de %lf\n", prom);
    return 0;
}

void generateWord(char *word)
{
    char *s = word;
    int upper = rand()%20 + 1;

    

    for (int i = 0; i < upper; i++)
    {
        *s++ = rand()%26 + 97;
    }

    *s = '\0';
}

char hasI(char *str)
{
    
    char *c = str;
    while (*c++ != '\0')
    {
        if (*c == 'i')
        {
            return 'N';
        }
    }
    return 'S';
}