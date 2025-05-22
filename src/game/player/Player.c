#include <stdlib.h>
#include <stdio.h>

#include "../world/village/Village.h"

#include "Player.h"

PlayerPtr createPlayer(VillagePtr currentVillage)
{
    PlayerPtr player = malloc(sizeof(*player));
    if (player == NULL)
    {
        perror("Error: Memory allocation failed for player.\n");
        exit(EXIT_FAILURE);
    }
    
    player->lives = INIT_LIVES;
    player->money = 0;
    player->canTravelBetweenWorlds = false;
    player->currentLocation = currentVillage; // Initialize to NULL or a default location
    
    return player;
}
