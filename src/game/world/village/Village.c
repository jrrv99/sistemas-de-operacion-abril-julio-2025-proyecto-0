#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../items/Item.h"
#include "../dungeon/Dungeon.h"
#include "../../../utils/utils.h"
#include "../../../game/game.h"

#include "Village.h"

static const char *DEFAULT_VILLAGE_TYPES[] = {
    "Aldea", "Villa", "Pueblo", "Bosque", "Poblado", "Dominio", "Ciudad"};

static const char *DEFAULT_VILLAGE_NAMES[] = {
    "Ordon", "Kakariko", "Hateno", "Lurelin", "Goron", "Zora", "Gerudo", "Rito"};

VillagePtr create_village(int id, bool isParallelWorld, VillagePtr counterpart, VillagePtr previous, VillagePtr next, int numOfVillages)
{
    VillagePtr village = malloc(sizeof(*village));
    /**
     * Calcula un valor único (salt) para generar el nombre de la aldea.
     * Si es un mundo paralelo, utiliza `id + numOfVillages` para garantizar
     * que el nombre sea único incluso entre aldeas normales y paralelas.
     * De lo contrario, utiliza solo el `id` de la aldea.
     */
    int saltForName = isParallelWorld ? id + numOfVillages : id;

    if (village == NULL)
    {
        perror("Error allocating memory for village\n");
        exit(EXIT_FAILURE);
    }

    char *name = generateName(
        DEFAULT_VILLAGE_TYPES, sizeof(DEFAULT_VILLAGE_TYPES) / sizeof(DEFAULT_VILLAGE_TYPES[0]),
        DEFAULT_VILLAGE_NAMES, sizeof(DEFAULT_VILLAGE_NAMES) / sizeof(DEFAULT_VILLAGE_NAMES[0]),
        saltForName);

    snprintf(village->name, sizeof(village->name), "%s", name);

    village->id = id;
    village->isParallelWorld = isParallelWorld;
    village->counterpart = counterpart;
    village->hiddenItem = NULL;

    Dungeon *dungeon = create_dungeon(id, saltForName);
    village->associatedDungeon = dungeon;
    dungeon->associatedVillage = village;

    // Initialize the linked list pointers
    village->previous = previous;
    village->next = next;

    return village;
}

VillagePtr create_village_list(int numOfVillages, bool isParallelWorld, VillagePtr normalListHead)
{
    if (isParallelWorld)
        assert(normalListHead != NULL && "Error: A list of normal villages is required to create the parallel world");

    VillagePtr head = NULL;
    VillagePtr previous = NULL;
    VillagePtr normalCursor = normalListHead;

    for (int id = 0; id < numOfVillages; id++)
    {
        VillagePtr counterpart = NULL;

        if (isParallelWorld && normalCursor != NULL)
        {
            counterpart = normalCursor;
        }

        VillagePtr newVillage = create_village(
            id,
            isParallelWorld,
            counterpart, // Aldea normal correspondiente
            previous,
            NULL,
            numOfVillages);

        if (counterpart != NULL)
        {
            counterpart->counterpart = newVillage; // Aldea paralela correspondiente a la normal
        }

        if (head == NULL)
        {
            head = newVillage; // Primera aldea
        }

        if (previous != NULL)
        {
            previous->next = newVillage;                                       // Enlace doble
            previous->associatedDungeon->next = newVillage->associatedDungeon; // Enlace entre mazmorras
        }

        previous = newVillage;

        if (normalCursor != NULL)
        {
            normalCursor = normalCursor->next;
        }
    }

    return head;
}

/**
 * Procesa el comando "busq" en una aldea
 */
void search_village(VillagePtr village)
{
    if (village->hiddenItem != NULL && !village->hiddenItem->found)
    {
        printf("¡Has encontrado %s!\n", village->hiddenItem->name);
        village->hiddenItem->found = true;
    }
    else if (village->associatedDungeon->requiredItem != NULL)
    {
        // Dar pista sobre el ítem para la mazmorra
        ItemPtr requiredItem = village->associatedDungeon->requiredItem;
        if (requiredItem->location != NULL)
        {
            if (requiredItem->locationType == LOCATION_VILLAGE)
            {
                VillagePtr itemVillage = (VillagePtr)requiredItem->location;
                printf("El ítem para derrotar la mazmorra %s está en la aldea %s.\n",
                       village->associatedDungeon->name, itemVillage->name);
            }
            else if (requiredItem->locationType == LOCATION_DUNGEON)
            {
                DungeonPtr itemDungeon = (DungeonPtr)requiredItem->location;
                printf("El ítem para derrotar la mazmorra %s está en la mazmorra %s.\n",
                       village->associatedDungeon->name, itemDungeon->name);
            }
        }
        else if (requiredItem->locationType == LOCATION_SHOP)
        {
            printf("El ítem para derrotar la mazmorra %s debe ser comprado en una tienda.\n",
                   village->associatedDungeon->name);
        }
    }
    else
    {
        printf("No encuentras nada útil aquí.\n");
    }
}
