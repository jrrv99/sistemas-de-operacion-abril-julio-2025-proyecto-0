#ifndef ITEM_H
#define ITEM_H

#include <stdbool.h>

// Fordward declarations
struct Dungeon;

typedef enum LocationType
{
    LOCATION_SHOP,    // Tienda (comprable)
    LOCATION_DUNGEON, // Mazmorras
    LOCATION_VILLAGE, // Aldea
} LocationType;

typedef struct Item
{
    int id;                    // ID del ítem
    char name[50];
    bool found;
    LocationType locationType; // Tipo de ubicación del ítem
    void* location; // Dónde se encuentra el ítem
    struct Dungeon *defeats;   // Qué mazmorra derrota este ítem
    struct Item *next;
} Item;

typedef struct Item *ItemPtr;

ItemPtr create_item(int id, int numOfItems);
ItemPtr create_item_list(int numOfItems, bool isParallelWorld);
void assign_items(VillagePtr villages, ItemPtr items);

#endif // ITEM_H
