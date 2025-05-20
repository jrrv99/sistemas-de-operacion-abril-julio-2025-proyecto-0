#include "Player.h"
#include <stdlib.h>
#include <stdio.h>

PlayerPtr createPlayer()
{
    PlayerPtr player = malloc(sizeof(Player));
    if (player == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for player.\n");
        exit(EXIT_FAILURE);
    }
    
    player->lives = INIT_LIVES;
    player->money = 0;
    player->currentLocation = NULL; // Initialize to NULL or a default location
    player->parallelWorldUnlocked = 0; // Initialize to 0 (locked)
    
    return player;
}