#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Message
{
    char autor[50];
    char content[200];
    char time[10];
} Message;

typedef struct Conversation
{
    Message *messages[100];
    int nMessages;
} Conversation;

char *inputString(FILE* fp, size_t *lenofS);
void getTimeString(char *string);


Message *createMessage(char *content, char *autor);
void modifyMessage(Message *m, char *newContent);
void freeMessage(Message *m);

void printMessage(Message *m);
void showConversation(Conversation *conv);
void editConversation(Conversation *conv);
void deleteConversation(Conversation *conv);

int main(int argc, char *argv[])
{
    Conversation *c = malloc(sizeof(Conversation));
    c->nMessages = 0;

    while (1)
    {
        if (c->nMessages == 99)
        {
            printf("Limite de mensajes alcanzado\n");
            break;
        }

        size_t ns, ms;
        printf("Usuario: ");
        char *name = inputString(stdin, &ns);

        printf("Escriba el mensaje: ");
        char *message = inputString(stdin, &ms);
  
        c->messages[c->nMessages++] = createMessage(message, name);

        //printMessage(c->messages[c->nMessages-1]);

        free(name);
        free(message);

        //printf("\n%s\n", m->content);

        int r;
        printf("Quiere seguir mandando mensajes? 1/0\n");
        scanf("%d", &r);
        getchar();

        if (!r)
        {
            break;
        }
    }

    showConversation(c);
    
    int r;
    printf("Quieres editar algun mensaje?1/0\n");
    scanf("%d", &r);
    getchar();

    if (r)
    {
        editConversation(c);
    }

    

    printf("Quieres eliminar algun mensaje?1/0\n");
    scanf("%d", &r);
    getchar();

    if (r)
    {
        deleteConversation(c);
    }

    free(c);
    return 0;
}

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

void getTimeString(char *string)
{
    // get current time
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    sprintf(string, "(%d:%d)", tm_struct->tm_hour, tm_struct->tm_min);
}

Message *createMessage(char *content, char *autor)
{
    Message *m  = (Message *) malloc(sizeof(Message));

    if (m == NULL)
    {
        printf("ERROR ALLOCATING MEMORY FOR MESSAGE\n");
        return NULL;
    }

    strcpy(m->content, content);
    strcpy(m->autor, autor);
    getTimeString(m->time);

    //printf("Message created: ");
    //printMessage(m);

    return m;
}
void modifyMessage(Message *m, char *newContent);
void freeMessage(Message *m);

void printMessage(Message *m)
{
    printf("\n%s %s: %s\n", m->time, m->autor, m->content);
}

void showConversation(Conversation *conv)
{
    printf("\n============Conversacion============\n");
    for (int i = 0; i < conv->nMessages; i++)
    {
        printMessage(conv->messages[i]);
    }
}

void editConversation(Conversation *conv)
{
    int selection;
    printf("Elija un numero del 0 al %d\n:", conv->nMessages - 1);

    scanf("%d", &selection);
    getchar();

    char *newMessage;
    size_t s;
    printf("Ingrese su nuevo texto:\n");
    newMessage = inputString(stdin, &s);
    strcpy(conv->messages[selection]->content, newMessage);

    showConversation(conv);
}

void deleteConversation(Conversation *conv)
{
    int selection;
    printf("Elija un numero del 0 al %d\n:", conv->nMessages - 1);

    scanf("%d", &selection);
    getchar();

    Conversation *newConv = malloc(sizeof(Conversation));

    newConv->nMessages = conv->nMessages-1;

    int count = 0;
    for (int i = 0; i < conv->nMessages; i++)
    {
        if (i != selection)
        {
            newConv->messages[count++] = conv->messages[i];
        }
    }

    showConversation(newConv);
    free(newConv);
}