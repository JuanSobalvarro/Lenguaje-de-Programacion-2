#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct node
{
    char c;
    float val;
    struct node *next;
} node;

int strtoint(char *s, int size);
char *getSubString(char *str, int idx0, int idx1);
char *getString(int *size);
int getInt();
float strtofloat(char *s);

char *sortPow(char *str);
float result(char *str);

int main()
{
    char *expression;
    int size;
    printf("Ingrese su expresion matematica: ");
    expression = getString(&size);

    printf("String: %s\n", expression);

    printf("Resultado de la expresion: %f", result(expression));



    return 0;
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

int getInt()
{
    int size;
    char *str = getString(&size);
    return strtoint(str, size);
}

char *sortPow(char *str)
{
    
}

int isOperation(char c)
{
    if (c == '-' || c == '+' || c == '*' || c == '/' || c == '^')
    {
        return 1;
    }

    return 0;
}

int isInt(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
}

float result(char *str)
{
    float result = 0;

    // create linked_lsit
    node *first = malloc(sizeof(node));

    int *nums = malloc(100 * sizeof(int));
    int *nhead = nums;
    char *ops = malloc(100);
    char *ophead = ops;

    int countOps = 0;
    int countNums = 0;

    // check if all the digits are valid for the expression
    int lastwasSpace = 1;
    int lastwasOp = 0;

    node *n = first;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!lastwasSpace && str[i] == ' ')
        {
            lastwasSpace = 1;
            lastwasOp = 0;
        }
        else if (lastwasSpace && isOperation(str[i]))
        {
            lastwasSpace = 0;
            lastwasOp = 1;
            *(ophead++) = str[i];
            countOps++;

            n->c = str[i];
            n->val = -1;
            n->next = (node *) malloc(sizeof(node));
            n = n->next;
        }
        else if (lastwasSpace && isInt(str[i]))
        {
            lastwasSpace = 0;
            *(nhead++) = str[i];
            countNums++;
            lastwasOp = 0;

            //n->c = NULL;
            //*n->val = str[i] - '0';
            n->next = (node *) malloc(sizeof(node));
            n = n->next;
        }
        else
        {
            printf("Operacion no valida\n");
            return 0;
        }
        
    }
    if (lastwasOp || lastwasSpace)
    {
        printf("Operacion no valida\n");
        return 0;
    }

    // once check if is a valid expression
    // we have a valid array of numbers and operation
   

    // look for power
    printf("Result: %f\n", result);
    return result;
}