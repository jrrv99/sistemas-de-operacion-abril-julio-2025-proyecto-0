#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>

// Fordward declarations
struct Item;
struct Village;
struct GameState;
typedef struct GameState *GameStatePtr;

typedef struct Dungeon
{
    int id; // ID de la mazmora
    char name[50];
    bool defeated;
    struct Item *requiredItem;         // Ítem necesario para derrotar
    struct Item *hiddenItem;           // Ítem oculto en esta mazmorra (puede ser NULL)
    struct Village *associatedVillage; // Aldea asociada a esta mazmorra
    struct Dungeon *next;
} Dungeon;

typedef struct Dungeon *DungeonPtr;

DungeonPtr create_dungeon(int id, int saltForName);
void search_dungeon(GameStatePtr game, DungeonPtr dungeon);
bool attack_dungeon(GameStatePtr game, DungeonPtr dungeon);

#endif // DUNGEON_H