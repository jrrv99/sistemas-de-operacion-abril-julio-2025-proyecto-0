#ifndef GAME_H
#define GAME_H

#include "world/world.h"
#include "player/Player.h"

typedef struct GameState
{
    WorldPtr upperWorld;
    WorldPtr parallelWorld;
    PlayerPtr player;
    bool parallelWorldUnlocked;
    int villagesToDefeatToUnlock;
} GameState;

typedef struct GameState *GameStatePtr;

int readNumOfVillages();
GameStatePtr initialize_game(int numOfVillages);
void shop_menu(GameStatePtr game);
void move_player(GameStatePtr game, VillagePtr destination);
void play();

#endif // GAME_H
