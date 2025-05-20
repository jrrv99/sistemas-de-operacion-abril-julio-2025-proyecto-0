#ifndef PLAYER_H
#define PLAYER_H

#define INIT_LIVES 3
#define MAX_LIVES 127


typedef struct Player
{
    int lives;
    int money;
    struct Village *currentLocation;
    int parallelWorldUnlocked;
} Player;

typedef struct Player *PlayerPtr;

PlayerPtr createPlayer();

#endif // PLAYER_H