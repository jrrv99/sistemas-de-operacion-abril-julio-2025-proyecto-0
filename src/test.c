#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils/utils.h"
#include "game/world/items/Item.h"

#define NUM_OF_VILLAGES 20

int main()
{
    srand(time(NULL));
    
    printf("Generando nombres de ítems Mundo Superior:\n");
    for (int i = 0; i < NUM_OF_VILLAGES; i++)
    {

        printf("%s\n", generateName(DEFAULT_ITEM_TYPES, sizeof(DEFAULT_ITEM_TYPES) / sizeof(DEFAULT_ITEM_TYPES[0]),
                                    DEFAULT_ITEM_NAMES, sizeof(DEFAULT_ITEM_NAMES) / sizeof(DEFAULT_ITEM_NAMES[0]),
                                    i));
    }

    printf("\nGenerando nombres de ítems Mundo Paralelo:\n");
    for (int i = 0; i < NUM_OF_VILLAGES; i++)
    {

        printf("%s\n", generateName(DEFAULT_ITEM_TYPES, sizeof(DEFAULT_ITEM_TYPES) / sizeof(DEFAULT_ITEM_TYPES[0]),
                                    DEFAULT_ITEM_NAMES, sizeof(DEFAULT_ITEM_NAMES) / sizeof(DEFAULT_ITEM_NAMES[0]),
                                    NUM_OF_VILLAGES+i));
    }

    return 0;
}
