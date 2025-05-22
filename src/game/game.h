#ifndef GAME_H
#define GAME_H

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

#endif // GAME_H
