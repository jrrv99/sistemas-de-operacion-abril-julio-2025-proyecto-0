#ifndef VILLAGE_H
#define VILLAGE_H

typedef struct Village
{
    char name[50];
    struct Dungeon *associatedDungeon;
    struct Item *hiddenItem;     // Ítem oculto en esta aldea (puede ser NULL)
    struct Village *counterpart; // Aldea correspondiente en mundo paralelo
    struct Village *previous;
    struct Village *next;
} Village;

#endif // VILLAGE_H
