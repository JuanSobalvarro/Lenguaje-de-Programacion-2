#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TEAM
{
    char *name;
    char *country;
    int coef;
    int inDraw;
} TEAM;

typedef struct PAIR
{
    TEAM *local;
    TEAM *visitor;
} PAIR;

typedef struct DRAW
{
    TEAM *teams[8];
    PAIR *pairs[4];
} DRAW;



DRAW *createDraw();
TEAM *createTeam(char *name, char *country, int coef);
void printDraw(DRAW *d);
void freeDraw(DRAW *d);

int main()
{
    DRAW *d = createDraw();
    printDraw(d);
    freeDraw(d);
    return 0;
}

TEAM *createTeam(char *name, char *ctry, int coef)
{
    TEAM *t = (TEAM*) malloc(sizeof(TEAM*));
    //printf("Allocating team %s %s %d\n", name, ctry, coef);
    

    t->name = malloc(20);
    memcpy(t->name, name, 20);
    t->country = malloc(20);
    memcpy(t->country, ctry, 20);
    t->coef = coef;

    t->inDraw = 0;

    return t;
}

void loadTeams(DRAW *draw)
{
    FILE *csv = fopen("C:/Clases/3.er Año/Primer Cuatrimestre/Lenguaje de Programacion 2/sorteoCuartos/equipos.csv", "r");

    if (!csv)
    {
        printf("ERROR::MOVEMENTS:: OPENING CSV FILE\n");
        return;
    } 

    char buffer[100];

    fgets(buffer, sizeof(buffer), csv);

    for (int i = 0; fgets(buffer, sizeof(buffer), csv); i++)
    {
        char nbuffer[100];

        char *name;
        char *country;
        int coef;
        strcpy(nbuffer, buffer);

        name = strtok(nbuffer, ",");
        country = strtok(NULL, ",");
        coef = atoi(strtok(NULL, ","));
        //printf("Creating team %s %s %d\n", name, country, coef);
        draw->teams[i] = createTeam(name, country, coef);
    }

}

PAIR *createPair(TEAM *loc, TEAM *vis)
{
    PAIR *p = (PAIR*) malloc(sizeof(PAIR*));

    p->local = loc;
    p->visitor = vis;

    return p;
}

void loadPairs(DRAW *d)
{
    srand(time(NULL));

    int nteams = 8;
    for (int i = 0; i < 4; i++)
    {
        int loc;
        int vis;
        
        while (d->teams[(loc = rand()%8)]->inDraw);
        while ((vis = rand()%8) == loc || d->teams[vis]->inDraw);

        d->teams[loc]->inDraw = 1;
        d->teams[vis]->inDraw = 1;
        d->pairs[i] = createPair(d->teams[loc], d->teams[vis]);
    }
}

DRAW *createDraw()
{
    DRAW *d = (DRAW*) malloc(sizeof(DRAW));

    loadTeams(d);

    loadPairs(d);

    return d;
}

void printDraw(DRAW *d)
{
    printf("==========IDA==========\n");
    for (int i = 0; i < 4; i++)
    {
        TEAM *loc = d->pairs[i]->local;
        TEAM *vis = d->pairs[i]->visitor;
        printf("Partido %d:\n", i + 1);
        printf("Local: %s %s %d\nvs\nVisitante: %s %s %d\n\n", loc->name, loc->country, loc->coef, vis->name, vis->country, vis->coef);
    }
    printf("==========VUELTA==========\n");
    for (int i = 0; i < 4; i++)
    {
        TEAM *vis = d->pairs[i]->local;
        TEAM *loc = d->pairs[i]->visitor;
        printf("Partido %d:\n", i + 1);
        printf("Local: %s %s %d\nvs\nVisitante%s %s %d\n\n", loc->name, loc->country, loc->coef, vis->name, vis->country, vis->coef);
    }
}

void freeDraw(DRAW *d)
{
    for (int i = 0; i < 4; i++)
    {
        TEAM* t1 = d->pairs[i]->local;
        TEAM* t2 = d->pairs[i]->visitor;
        
        free(t1->name);
        free(t1->country);
        free(t2->name);
        free(t2->country);

        free(t1);
        free(t2);

        free(d->pairs[i]);
    }

    free(d);
}