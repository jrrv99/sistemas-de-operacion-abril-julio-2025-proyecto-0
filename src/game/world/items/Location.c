#include "Location.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

LocationPtr createLocation(LocationType type, void *place)
{
    assert(type == LOCATION_SHOP || type == LOCATION_DUNGEON || type == LOCATION_VILLAGE);

    LocationPtr newLocation = (LocationPtr)malloc(sizeof(Location));

    newLocation->type = type;

    switch (type)
    {
        case LOCATION_SHOP:
            newLocation->place.shop = NULL;
            break;
        case LOCATION_DUNGEON:
            newLocation->place.dungeon = place;
            break;
        case LOCATION_VILLAGE:
            newLocation->place.village = place;
            break;
        default:
            perror("Error: Invalid location type\n");
            free(newLocation);
            return NULL;
    }

    return newLocation;
}

LocationPtr createShopLocation(void)
{
    return createLocation(LOCATION_SHOP, NULL);
}

LocationPtr createDungeonLocation(struct Dungeon *dungeon)
{
    return createLocation(LOCATION_DUNGEON, dungeon);
}

LocationPtr createVillageLocation(struct Village *village)
{
    return createLocation(LOCATION_VILLAGE, village);
}
