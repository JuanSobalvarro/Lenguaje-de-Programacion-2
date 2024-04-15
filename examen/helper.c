#include "helper.h"

/*
    input a string of an unsigned int and it returns a int
*/
int strtoint(char *s, int size)
{
    char c;
    char *str;
    str = s;
    int count;
    int num = 0;

    for (int i = 0; i < size; i++)
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
        {
            printf("String is not an unsigned number\n");
            return 0;
        }
        num += (s[i]-48) * pow(10, size-i-1);
    }

    return num;
}

int compStr(char *str1, char *str2)
{
    char *s1, *s2;
    s1 = str1;
    s2 = str2;
    while (*s1 != '\0' || *s2 != '\0')
    {
        if (*(s1++) != *(s2++))
        {
            return 0;
        }
    }

    return 1;
}



char *getString(int *size)
{
    FILE *fp = stdin;
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

    *size = len-1;

    return realloc(str, sizeof(*str)*len);
}

int getInt()
{
    int size;
    char *str = getString(&size);
    return strtoint(str, size);
}


