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
    bool found;                 // 0 = no encontrado, 1 = encontrado
    struct Location *location; // Dónde se encuentra el ítem
    struct Dungeon *defeats;   // Qué mazmorra derrota este ítem
    struct Item *next;
} Item;

typedef struct Item *ItemPtr;

static const char *DEFAULT_ITEM_TYPES[] = {
    "Espada", "Escudo", "Arco", "Bomba", "Gancho", "Boomerang", "Flauta", "Martillo"};

static const char *DEFAULT_ITEM_NAMES[] = {
    "Maestra", "Hyliano", "Luz", "Agua", "Ganondorf", "Fuego", "Vientos", "Dioses", "Espíritu", "Sombra", "Fuego", "Hielo", "Tierra", "Aire", "Rayo"};

#endif // ITEM_H
