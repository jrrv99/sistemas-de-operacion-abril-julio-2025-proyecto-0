#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>

// Fordward declarations
struct Item;
struct Village;

typedef struct Dungeon
{
    char name[50];
    bool defeated;
    struct Item *requiredItem;         // Ítem necesario para derrotar
    struct Item *hiddenItem;           // Ítem oculto en esta mazmorra (puede ser NULL)
    struct Village *associatedVillage; // Aldea asociada a esta mazmorra
    struct Dungeon *next;
} Dungeon;

#endif // DUNGEON_H