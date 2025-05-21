#ifndef DUNGEON_H
#define DUNGEON_H

#include <stdbool.h>

// Fordward declarations
struct Item;
struct Village;

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

static const char *DEFAULT_DUNGEON_TYPES[] = {
    "Mazmorras", "Cueva", "Ruinas", "Templo", "Fortaleza", "Castillo", "Cripta", "Palacio", "Gruta", "Catacumbas", "Mina", "Torre", "Santuario", "Caverna"};

static const char *DEFAULT_DUNGEON_NAMES[] = {
    "Agua", "Tierra", "Fuego", "Aire", "Bosque", "Sombra", "Espíritu", "Luz"};

#endif // DUNGEON_H