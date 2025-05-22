#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game/game.h"

int main()
{
    srand((unsigned int)time(NULL));

    play();
    
    return 0;
}

