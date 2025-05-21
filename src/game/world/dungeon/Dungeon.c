#include <stdlib.h>
#include <stdio.h>

#include "../../../utils/utils.h"
#include "../village/Village.h"
#include "Dungeon.h"

static const char *DEFAULT_DUNGEON_TYPES[] = {
    "Mazmorras", "Cueva", "Ruinas", "Templo", "Fortaleza", "Castillo", "Cripta", "Palacio", "Gruta", "Catacumbas", "Mina", "Torre", "Santuario", "Caverna"};

static const char *DEFAULT_DUNGEON_NAMES[] = {
    "Agua", "Tierra", "Fuego", "Aire", "Bosque", "Sombra", "Espíritu", "Luz"};

DungeonPtr create_dungeon(int id, int saltForName)
{
    DungeonPtr dungeon = malloc(sizeof(*dungeon));

    if (dungeon == NULL)
    {
        perror("Error allocating memory for dungeon\n");
        exit(EXIT_FAILURE);
    }
    
    char *name = generateName(
        DEFAULT_DUNGEON_TYPES, sizeof(DEFAULT_DUNGEON_TYPES) / sizeof(DEFAULT_DUNGEON_TYPES[0]),
        DEFAULT_DUNGEON_NAMES, sizeof(DEFAULT_DUNGEON_NAMES) / sizeof(DEFAULT_DUNGEON_NAMES[0]),
        saltForName);

    snprintf(dungeon->name, sizeof(dungeon->name), "%s", name);

    free(name); // Free the name after using it

    dungeon->id = id;
    dungeon->defeated = false;
    dungeon->requiredItem = NULL; // Initialize to NULL
    dungeon->hiddenItem = NULL;   // Initialize to NULL
    dungeon->associatedVillage = NULL; // Initialize to NULL
    dungeon->next = NULL; // Node for linked list

    return dungeon;
}