#ifndef VILLAGE_H
#define VILLAGE_H

#include <stdbool.h>

// Forward declarations
struct Dungeon;
struct Item;
struct GameState;
typedef struct GameState *GameStatePtr;

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

VillagePtr create_village(int id, bool isParallelWorld, VillagePtr counterpart, VillagePtr previous, VillagePtr next, int numOfVillages);
VillagePtr create_village_list(int numOfVillages, bool isParallelWorld, VillagePtr normalListHead);
void search_village(VillagePtr village);

#endif // VILLAGE_H
