#include "notes.h"
#include <stdlib.h>
#include <stdio.h>

char Cscale[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
char *names[] = {"Agregar Nota", "Eliminar Nota", "Mostrar Nota", "Construir Acorde"};

int idxInString(char *str, char val, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (str[i] == val)
        {
            return i;
        }
    }
    return -1;
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

    *lenofS = len-1;

    return realloc(str, sizeof(*str)*len);
}



void addNote(NOTES *n)
{
    char input;
    char *str;
    do
    {
        system("CLS");
        printf("==============Agregar notas==============\n");
        size_t len;
        printf("Ingrese una nota en la escala de Do Mayor: ");
        str = inputString(stdin, &len);
        input = str[0];
        if (input >= 97)
        {
            input -= 32;
        }
    } while (idxInString(Cscale, input, 7) == -1);

    n->currentNotes = (char *) realloc(n->currentNotes, sizeof(*n->currentNotes) * (n->nCurrentNotes+1));
    n->currentNotes[n->nCurrentNotes++] = input;
    free(str);
}

void eraseNote(NOTES *n)
{   
    getchar();
    char input;
    int idx;
    do
    {
        system("CLS");
        printf("==============Borrar nota==============\n");
        for (int i = 0; i < n->nCurrentNotes; i++)
        {
            printf("Nota %d: %c\n", i+1, n->currentNotes[i]);
        }
        printf("Elija la nota a borrar: ");
        scanf("%c", &input);
        getchar();
        idx = input - 48;
    } while (idx <= 0 || idx > n->nCurrentNotes+1);
    
    // remove cahraceter from array
    idx--; // - 1 so it starts at 0 in any case
    for (int i = idx; i < n->nCurrentNotes - 1; i++)
    {
        n->currentNotes[i] = n->currentNotes[i+1];
    }
    n->currentNotes = (char *) realloc(n->currentNotes, sizeof(*n->currentNotes) * (--n->nCurrentNotes));
}

void showNotes(NOTES *n)
{
    getchar();
    printf("==============Mostrar notas==============\n");
    for (int i = 0; i < n->nCurrentNotes; i++)
    {
        printf("Nota %d: %c\n", i+1, n->currentNotes[i]);
    }
}

/*
    If the chord is a valid basic chord in Cscale it returns the fundamental note, else it returns 0
*/
char validChord(char *chord, int len)
{
    // flags for third or fifth found
    int third = 0;
    int fifth = 0;

    // fundamental note
    char fundamental = '0';
    // in theory the fundamental note is at a distance of 2 and 4 notes from its third and fifth, if the array meets these conditions we have a chord
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            int idxFund = idxInString(Cscale, chord[i], 7);
            if (j != i)
            {
                int idxNote = idxInString(Cscale, chord[j], 7);
                // if moving 2 and 4 notes we match our notes, we have a valid chord
                if (Cscale[(idxFund+2)%7] == chord[j])
                {
                    third = 1;
                }
                else if (Cscale[(idxFund+4)%7] == chord[j])
                {
                    fifth = 1;
                }
            }
        }
        if (third && fifth)
        {
            fundamental = chord[i];
            break;
        }
    }
}

/*
    Construye un acorde a partir de unas notas de entrada, 
    checkea si estan dentro de las notas entrantes y devuelve el tipo de acorde
*/
void constructChord(NOTES *n)
{
    getchar();
    printf("==============Construir acorde==============\n");
    size_t len;

    printf("Notas validas: ");
    for (int i = 0; i < n->nCurrentNotes; i++)
    {
        printf("%c,", n->currentNotes[i]);
    }
    printf("\n");

    char *uwu;
    do
    {
        printf("Inserte su acorde(example: CDE): \n");
        uwu = inputString(stdin, &len);
        //printf("\nstring %s with len %d\n", uwu, len);
    } while (len != 3);

    // chequear si esta agregado en array
    for (int i = 0; i < len; i++)
    {
        if (idxInString(n->currentNotes, uwu[i], n->nCurrentNotes) == -1)
        {
            printf("Nota %c no encontrada en array\n", uwu[i]);
            free(uwu);
            return;
        }
    }

    char fundamental;
    if ((fundamental = validChord(uwu, len)) == '0')
    {
        printf("No se puede crear acorde basico con las notas %s\n", uwu);
        free(uwu);
        return;
    }
    
    printf("Chord builded: %c", fundamental);
    if (fundamental == 'B')
    {
        printf("dism");
    }
    else if (fundamental == 'D' || fundamental == 'E' || fundamental == 'A')
    {
        printf("-");
    }
    printf("\n");

    free(uwu);
}

void (*functions[])(NOTES *) = {addNote, eraseNote, showNotes, constructChord};

NOTES *initializeNotes()
{
    NOTES *n = (NOTES*) malloc(sizeof(NOTES));

    if (n == NULL)
    {
        return NULL;
    }

    n->nCurrentNotes = 0;
    n->currentNotes = malloc(sizeof(char) * n->nCurrentNotes);

    n->functions = functions;
    n->functionsNumber = 4;
    n->functionNames = names;
    
    return n;
}