#include <stdlib.h>
#include <stdio.h>

#include "world.h"

WorldPtr createWorld(int numOfVillages, int isParallel, WorldPtr normalWorld)
{
    WorldPtr world = malloc(sizeof(*world));

    if (world == NULL)
    {
        perror("Error allocating memory for world\n");
        exit(EXIT_FAILURE);
    }

    world->numOfVillages = numOfVillages;
    world->items = create_item_list(numOfVillages, isParallel);

    // Verifica si normalWorld es NULL antes de acceder a sus miembros
    VillagePtr normalVillages = NULL;
    if (normalWorld != NULL)
    {
        normalVillages = normalWorld->villages;
    }

    world->villages = create_village_list(numOfVillages, isParallel, normalVillages);
    world->defeatedDungeons = 0;
    world->isParallel = isParallel;

    assign_items(world->villages, world->items);

    return world;
}