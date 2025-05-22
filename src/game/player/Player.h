#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#define INIT_LIVES 3
#define MAX_LIVES 127

// Forward declarations
struct Village;

typedef struct Player
{
    int lives;
    int money;
    bool canTravelBetweenWorlds;
    struct Village *currentLocation;
} Player;

typedef struct Player *PlayerPtr;

PlayerPtr createPlayer();

#endif // PLAYER_H