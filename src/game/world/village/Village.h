#ifndef VILLAGE_H
#define VILLAGE_H

#include <stdbool.h>

// Fordward declarations
struct Dungeon;
struct Item;

typedef struct Village
{
    int id; // ID de la aldea
    char name[50];
    struct Dungeon *associatedDungeon;
    struct Item *hiddenItem;     // Ítem oculto en esta aldea (puede ser NULL)
    struct Village *counterpart; // Aldea correspondiente en mundo paralelo
    bool isParallelWorld;      // Indica si la aldea es del mundo paralelo
    struct Village *previous;
    struct Village *next;
} Village;

typedef struct Village *VillagePtr;

static const char *DEFAULT_VILLAGE_TYPES[] = {
    "Aldea", "Villa", "Pueblo", "Bosque", "Pobrado", "Dominio", "Ciudad"};

static const char *DEFAULT_VILLAGE_NAMES[] = {
    "Ordon", "Kakariko", "Hateno", "Lurelin", "Goron", "Zora", "Gerudo", "Rito"};

#endif // VILLAGE_H
