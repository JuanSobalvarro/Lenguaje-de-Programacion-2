#ifndef NOTES_H
#define NOTES_H

typedef struct notes
{
    char *currentNotes;
    int nCurrentNotes;
    void (**functions)();
    char **functionNames;
    int functionsNumber;
} NOTES;

NOTES *initializeNotes();

#endif