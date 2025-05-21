#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

// Fordward declarations
struct Location;
struct Dungeon;

typedef struct Item
{
    int id;                    // ID del ítem
    char name[50];
    bool found;
    struct Location *location; // Dónde se encuentra el ítem
    struct Dungeon *defeats;   // Qué mazmorra derrota este ítem
    struct Item *next;
} Item;

typedef struct Item *ItemPtr;

ItemPtr create_item(int id, int numOfItems);
ItemPtr create_item_list(int numOfItems, bool isParallelWorld);

#endif // ITEM_H
