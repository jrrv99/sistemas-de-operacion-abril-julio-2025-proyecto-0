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
    world->items = create_item_list(numOfVillages, isParallel); // Initialize items to NULL or allocate as needed
    world->villages = create_village_list(numOfVillages, isParallel, normalWorld->villages);
    world->defeatedDungeons = 0;
    world->isParallel = isParallel;

    assign_items(world->villages, world->items);

    return world;
}