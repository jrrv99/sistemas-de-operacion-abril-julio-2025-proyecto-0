#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils/utils.h"
#include "game/world/dungeon/Dungeon.h"
#include "game/world/village/Village.h"
#include "game/world/items/Item.h"

void print_world_map(VillagePtr normalHead, VillagePtr parallelHead)
{

    VillagePtr n = normalHead;
    VillagePtr p = parallelHead;

    printf("\n🗺️  MAPA DE CONEXIONES ENTRE MUNDOS\n");
    printf("──────────────────────────────────────────────────────────────\n");
    printf("🌍 Mundo Normal\t\t<--> 🌌 Mundo Paralelo\n");
    printf("──────────────────────────────────────────────────────────────\n");

    while (n != NULL && p != NULL)
    {
        printf("Aldea: %-20s <--> Aldea: %-20s\n", n->name, p->name);

        const char *dungeonN = (n->associatedDungeon != NULL) ? n->associatedDungeon->name : "Sin mazmorra";
        const char *dungeonP = (p->associatedDungeon != NULL) ? p->associatedDungeon->name : "Sin mazmorra";

        printf("Mazmorra: %-18s     Mazmorra: %-18s\n", dungeonN, dungeonP);
        printf("──────────────────────────────────────────────────────────────\n");

        n = n->next;
        p = p->next;
    }

    if (n != NULL || p != NULL)
    {
        printf("⚠️  Las listas no están completamente sincronizadas.\n");
    }
}

void test_village_travel(VillagePtr start)
{
    VillagePtr current = start;

    printf("Simulación de viaje %s:\n\n", current->isParallelWorld ? "en el mundo paralelo" : "en el mundo normal");

    while (current != NULL)
    {
        printf("🏘️  Aldea: %s\n", current->name);

        if (current->associatedDungeon)
        {
            printf("🕳️  Entrando en mazmorra: %s\n", current->associatedDungeon->name);
        }
        else
        {
            printf("⚠️  No hay mazmorra asociada\n");
        }

        // Simula salir de la mazmorra e ir a la siguiente aldea
        current = current->associatedDungeon->associatedVillage->next;

        printf("➡️  Viajando a la siguiente aldea...\n\n");
    }

    printf("🏁 Fin del recorrido\n");
}

void test_item_lists(ItemPtr itemsList)
{
    printf("=== Normal World Items ===\n");
    ItemPtr item = itemsList;

    while (item != NULL)
    {
        printf("Item ID: %d, Name: %s, ", item->id, item->name);

        if (item->location == NULL)
        {
            printf("🏪 Tienda");
        }
        else if (item->locationType == LOCATION_VILLAGE)
        {
            printf("🏘️ Aldea: %s", ((Village *)item->location)->name);
        }
        else if (item->locationType == LOCATION_DUNGEON)
        {
            printf("🕳️ Mazmorra: %s", ((Dungeon *)item->location)->name);
        }

        printf("\n");

        item = item->next;
    }
}

int main()
{
    srand(time(NULL)); // Inicializa aleatoriedad solo una vez

    int numOfVillages = 5; // Number of items to create
    VillagePtr normalHead = create_village_list(numOfVillages, false, NULL);
    VillagePtr parallelHead = create_village_list(numOfVillages, true, normalHead);

    ItemPtr itemsList = create_item_list(numOfVillages, false);
    ItemPtr parallelItems = create_item_list(numOfVillages, true);
    print_world_map(normalHead, parallelHead);

    assign_items(normalHead, itemsList);
    printf("\n");
    assign_items(parallelHead, parallelItems);

    printf("\n");

    // test_village_travel(upperList);
    test_item_lists(itemsList);
    printf("\n");
    test_item_lists(parallelItems);

    return 0;
}
