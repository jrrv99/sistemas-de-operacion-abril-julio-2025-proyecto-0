#include <stdlib.h>
#include <stdio.h>

#include "../village/Village.h"
#include "../items/Item.h"
#include "../../../game/game.h"
#include "../../../utils/utils.h"

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

/**
 * Procesa el comando "busq" en una mazmorra
 */
void search_dungeon(GameStatePtr game, DungeonPtr dungeon)
{
    static bool alreadySearched = false;

    if (alreadySearched)
    {
        printf("Ya has buscado aquí. ¡Un monstruo te ataca!\n");
        game->player->lives--;
        printf("Pierdes una vida. Vidas restantes: %d\n", game->player->lives);
        return;
    }

    if (dungeon->hiddenItem != NULL && !dungeon->hiddenItem->found)
    {
        printf("¡Has encontrado %s!\n", dungeon->hiddenItem->name);
        dungeon->hiddenItem->found = true;
    }
    else
    {
        printf("No encuentras ningún ítem, pero encuentras $10 en el suelo.\n");
        game->player->money += 10;
    }

    alreadySearched = true;
}

/**
 * Procesa el comando "atac" en una mazmorra
 */
bool attack_dungeon(GameStatePtr game, DungeonPtr dungeon)
{
    if (dungeon->defeated)
    {
        printf("Esta mazmorra ya ha sido derrotada.\n");
        return false;
    }

    ItemPtr requiredItem = dungeon->requiredItem;

    if (requiredItem == NULL)
    {
        printf("Error: Esta mazmorra no tiene ítem requerido.\n");
        return false;
    }

    if (!requiredItem->found)
    {
        printf("¡No tienes el ítem necesario para derrotar esta mazmorra!\n");
        printf("Necesitas: %s\n", requiredItem->name);
        game->player->lives--;
        printf("Pierdes una vida. Vidas restantes: %d\n", game->player->lives);
        return false;
    }

    printf("¡Usas %s y derrotas la mazmorra %s!\n", requiredItem->name, dungeon->name);
    dungeon->defeated = true;
    game->upperWorld->defeatedDungeons++;

    // Verificar si esta es la mazmorra que desbloquea el mundo paralelo
    if (!game->parallelWorldUnlocked &&
        game->upperWorld->defeatedDungeons >= game->villagesToDefeatToUnlock)
    {
        printf("\n¡Has derrotado suficientes mazmorras para desbloquear el mundo paralelo!\n");
        game->parallelWorld = createWorld(game->upperWorld->numOfVillages, true, game->upperWorld);
        game->parallelWorldUnlocked = true;

        // Transportar al jugador al mundo paralelo
        game->player->currentLocation = game->parallelWorld->villages;
        printf("Te transportas al mundo paralelo...\n");
        return true;
    }

    // Verificar si es la primera mazmorra del mundo paralelo
    if (game->parallelWorldUnlocked && game->upperWorld->isParallel && dungeon->id == 0)
    {
        printf("\n¡Has derrotado la primera mazmorra del mundo paralelo!\n");
        printf("Ahora puedes viajar libremente entre los dos mundos.\n");
        game->player->canTravelBetweenWorlds = true;
    }

    // Verificar si se han derrotado todas las mazmorras
    if (game->parallelWorldUnlocked)
    {
        int totalDungeons = game->upperWorld->numOfVillages * 2; // Ambos mundos
        int defeatedDungeons = game->upperWorld->defeatedDungeons;
        if (game->parallelWorld)
        {
            defeatedDungeons += game->parallelWorld->defeatedDungeons;
        }

        if (defeatedDungeons >= totalDungeons)
        {
            printf("\n¡FELICIDADES! ¡Has derrotado todas las mazmorras y completado el juego!\n");
            return true; // Juego completado
        }
    }

    return false;
}