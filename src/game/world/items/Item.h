#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

// Fordward declarations
struct Location;
struct Dungeon;

typedef struct Item
{
    char name[50];
    bool found;                 // 0 = no encontrado, 1 = encontrado
    struct Location *location; // Dónde se encuentra el ítem
    struct Dungeon *defeats;   // Qué mazmorra derrota este ítem
    struct Item *next;
} Item;

#endif // ITEM_H
