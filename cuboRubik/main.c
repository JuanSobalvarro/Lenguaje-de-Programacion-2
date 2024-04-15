#include <stdio.h>
#include <stdlib.h>

// ANSI escape code
#define RED "\e[38;5;196m"
#define GRN "\e[38;5;40m"
#define YEL "\e[38;5;226m"
#define BLU "\e[38;5;21m"
#define ORA "\e[38;5;214m"
#define WHT "\e[38;5;231m"
#define DEFAULT "\e[m"

/*
    Faces will show as:
            white
        red blue green orange
            yellow
*/
char facesColor[][12] = {WHT, RED, BLU, GRN, ORA, YEL};

typedef struct CARA
{
    char *color;
} CARA;

typedef struct CUBO
{
    CARA *faces[6];
} CUBO;

CARA *initializeFace(char *color);
CUBO *initializeCube();
void showCube(CUBO *cube);

int main()
{   
    CUBO *c = initializeCube();

    showCube(c);

    return 0;
}

CARA *initializeFace(char *color)
{
    CARA *c = (CARA*) malloc(sizeof(CARA));
    for (int i = 0; i < 3; i++)
    {
        c->color = color;
    }
    return c;
}

CUBO *initializeCube()
{
    CUBO *c = (CUBO*) malloc(sizeof(CUBO));

    // create the 6 faces
    for (int i = 0; i < 6; i++)
    {
        c->faces[i] = initializeFace(facesColor[i]);
    }

    return c;
}

void printTopBot(char *color)
{
    for (int i = 0; i < 3; i++)
    {
        printf("   ");
        printf("%s\u2588\u2588\u2588\n", color);
    }
}

void printMid(char **colors)
{
    //print mid colors
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%s\u2588\u2588\u2588", colors[j]);
        } 
        printf("\n");
    }
    
}

void showCube(CUBO *cube)
{
    // print white

    char *colors[20] = {cube->faces[1]->color, cube->faces[2]->color, cube->faces[3]->color, cube->faces[4]->color};
    
    printTopBot(cube->faces[0]->color);
    printMid(colors);
    printTopBot(cube->faces[5]->color);
    printf("%s", DEFAULT);
}