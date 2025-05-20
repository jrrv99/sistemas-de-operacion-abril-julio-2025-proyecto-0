#ifndef WORLD_H
#define WORLD_H

// Fordward declarations
struct Village;
struct Dungeon;
struct Item;

typedef struct World
{
    Village *villages; // Lista de aldeas
    Dungeon *dungeons; // Lista de mazmorras
    Item *items;       // Lista de ítems
    int villageCount;  // Número de aldeas/mazmorras
    int isParallel;    // 0 = mundo superior, 1 = mundo paralelo
} World;

#endif // WORLD_H
