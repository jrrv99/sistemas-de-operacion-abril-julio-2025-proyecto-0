#ifndef WORLD_H
#define WORLD_H

// Fordward declarations
#include "village/Village.h"
#include "dungeon/Dungeon.h"
#include "items/Item.h"

typedef struct World
{
    int numOfVillages; // Número de aldeas
    Village *villages; // Lista de aldeas
    Item *items;       // Lista de ítems
    int defeatedDungeons; // Número de mazmorras derrotadas
    int isParallel;    // 0 = mundo superior, 1 = mundo paralelo
} World;

typedef struct World *WorldPtr;

WorldPtr createWorld(int numOfVillages, int isParallel, WorldPtr normalWorld);

#endif // WORLD_H
