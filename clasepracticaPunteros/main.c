#include <stdio.h>
#include <stdlib.h>

const char vocals[] = {'a','e','i','o','u','A','E','I','O','U'};

char *getText(FILE *fp, int *lenOfString)
{
    // string pointer
    char *str;
    int ch;
    size_t len = 0;
    //size_t size = 10;

    // re allocalize memory to our necessary size
    str = realloc(NULL, sizeof(*str) * len);

    // if couldnt reallocate memory return str
    if (!str)
    {
        return str;
    }

    // fgetc returns a readed unsigned char in the file casted to a int. EOF means end of file
    while (EOF != (ch = fgetc(fp)) && ch != '\n')
    {
        str[len++] = ch;
        str = realloc(str, sizeof(*str)*(len));
        if(!str)
        {
            return str;
        }
    }
    str[len++] = '\0';

    *lenOfString = len;

    return realloc(str, sizeof(*str)*len);
}

int checkPuntuacion(char c)
{
    if (c == '.' || c == ',' || c == ';' || c == ':' || c == ' ')
    {
        return 1;
    }
    return 0;
}

int checkVocal(char c)
{
    for (int i = 0; i < 10; i++)
    {
        if (c == vocals[i])
        {
            return 1;
        }
    }
    return 0;
}

int checkConsonante(char c)
{
    //printf("Checking c %d: %c\n", c);
    // check uppercase and lowercase
    if ((c > 'A' && c <= 'Z') || (c > 'a' && c <= 'z'))
    {
        return 1;
    }
    return 0;
}

int *valuesQuantity(char *text, int len)
{
    int *values; // 0->words, 1->consonantes, 2->vocals, 3-7->a,e,i,o,u  
    values = malloc(8 * sizeof(int));
    for (int i = 0; i < 8; i++)
    {
        values[i] = 0;
    }

    char lastchar = 'a';
    for (int i = 0; i <= len; i++)
    {
        // check for space
        if (text[i] == ' ' || text[i]  == '\0')
        {
            if (!checkPuntuacion(lastchar))
            {
                values[0]++;
            }
        }
        else if(checkVocal(text[i]))
        {
            char vocal = text[i];
            if (vocal > 90)
            {
                vocal -= 32;
            }
            switch(text[i])
            {
                case 'a':
                    values[3]++;
                    break;
                case 'e':
                    values[4]++;
                    break;
                case 'i':
                    values[5]++;
                    break;
                case 'o':
                    values[6]++;
                    break;
                case 'u':
                    values[7]++;
                    break;
            }
            values[2]++;
        }
        // if none of the cases worked it only means it has to be a consonante or other symbol
        else if (checkConsonante(text[i]))
        {
            values[1]++;
        }
        lastchar = text[i];
    }

    return values;
}

int main()
{
    char *text;
    int len;
    int *count;
    
    printf("Ingrese el texto que desee encontrar el numero de palabras, vocales y consonantes:\n");

    text = getText(stdin, &len);

    printf("\n%s\n", text);
    
    count = valuesQuantity(text, len);
    
    printf("El usuario ha ingresado:\n%d Palabras\n%d Consonantes\n%d Vocales\n", count[0], count[1], count[2]);
    printf("Donde en vocales tenemos que hay:\n%d 'A'\n%d 'E'\n%d 'I'\n%d 'O'\n%d 'U'\n", count[3], count[4], count[5], count[6], count[7]);

    free(count);
    return 0;
}