

#include <stdlib.h>
#include <stdio.h>

/*
    Returns a pointer to a string of
    a size depending on the input.
    Where the input can be any type of file
    and the lenofS is a pointer to a size_int to save
    string lenght.
*/
char *inputString(FILE* fp, size_t *lenofS)
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

    *lenofS = len;

    return realloc(str, sizeof(*str)*len);
}

/*
    Check if a string is a real number 
*/
int isNum(char *s)
{
    char *str;
    str = s;

    char c;
    int point_count = 0;

    // if the first digit is not a minus sign or a number is no t anumber
    if((c = *(str++)) != '-' &&  !(c >= '0' && c <= '9'))
    {
        //printf("\nsign\n");
        return 0;
    }

    while ((c = *(str++)) != '\0')
    {
        if (c == '.')
        {
            if (++point_count > 1)
            {
                //printf("\npoint\n");
                return 0;
            } 
        }
        else if (!(c >= '0' && c <= '9'))
        {
            //printf("\ndigit\n");
            return 0;
        }
    }

    return 1;

}

void *copymemory(void *dest, const void *src, size_t count)
{
    char *tmp = dest;
    const char *s = src;

    while (count != 0)
    {
        *tmp++ = *s++;
        --count;
    }
    return dest;
}
