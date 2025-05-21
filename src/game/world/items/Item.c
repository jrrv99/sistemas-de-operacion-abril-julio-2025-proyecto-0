#include <stdlib.h>
#include <stdio.h>

#include "../../../utils/utils.h"
#include "../village/Village.h"
#include "../dungeon/Dungeon.h"
#include "Item.h"

static const char *DEFAULT_ITEM_TYPES[] = {
    "Espada", "Escudo", "Arco", "Bomba", "Gancho", "Boomerang", "Flauta", "Martillo"};

static const char *DEFAULT_ITEM_NAMES[] = {
    "Maestra", "Hyliano", "Luz", "Agua", "Ganondorf", "Fuego", "Vientos", "Dioses", "Espíritu", "Sombra", "Fuego", "Hielo", "Tierra", "Aire", "Rayo"};

ItemPtr create_item(int id, int saltForName)
{
    ItemPtr newItem = malloc(sizeof(*newItem));

    newItem->id = id;
    newItem->found = false;
    newItem->location = NULL; // Se asignará después
    newItem->defeats = NULL;  // Se asignará después
    newItem->next = NULL;

    char *name = generateName(
        DEFAULT_ITEM_TYPES, sizeof(DEFAULT_ITEM_TYPES) / sizeof(DEFAULT_ITEM_TYPES[0]),
        DEFAULT_ITEM_NAMES, sizeof(DEFAULT_ITEM_NAMES) / sizeof(DEFAULT_ITEM_NAMES[0]),
        saltForName + id); // Use id as salt for name generation

    snprintf(newItem->name, sizeof(newItem->name), "%s", name);

    return newItem;
}

ItemPtr create_item_list(int numOfItems, bool isParallelWorld)
{
    if (numOfItems <= 0)
        return NULL;

    int saltForName = isParallelWorld ? numOfItems : 0;

    ItemPtr head = NULL;
    ItemPtr previous = head;

    for (int id = 0; id < numOfItems; id++)
    {
        ItemPtr newItem = create_item(id, saltForName);

        if (head == NULL)
        {
            head = newItem; // Primera aldea
        }

        if (previous != NULL)
        {
            previous->next = newItem; // Conectar el nuevo ítem a la lista
        }

        previous = newItem; // Mover el puntero al nuevo ítem
    }

    return head;
}

void assign_items(VillagePtr villages, ItemPtr items)
{
    // Recorrer las aldeas y mazmorras del mundo normal
    VillagePtr currentVillage = villages;
    DungeonPtr currentDungeon;
    // ItemPtr firstItem = items; // Guardar referencia al primer ítem

    while (currentVillage != NULL)
    {
        currentDungeon = currentVillage->associatedDungeon;

        // 1. Asignar ítem oculto a la aldea (si el número es par)
        if (rand() % 2 == 0)
        { // Número par
            // Buscar un ítem no asignado
            ItemPtr item = items;
            while (item != NULL && item->location != NULL)
            {
                item = item->next;
            }

            if (item != NULL)
            {
                currentVillage->hiddenItem = item;
                item->location = (struct Location *)currentVillage;
                printf("Ítem %s asignado a la aldea %s\n", item->name, currentVillage->name);
            }
        }

        // 2. Asignar ítem oculto a la mazmorra (si el número es par)
        if (rand() % 2 == 0)
        { // Número par
            // Buscar un ítem no asignado
            ItemPtr item = items;
            while (item != NULL && item->location != NULL)
            {
                item = item->next;
            }

            if (item != NULL)
            {
                currentDungeon->hiddenItem = item;
                item->location = (struct Location *)currentDungeon;
                printf("Ítem %s asignado a la mazmorra %s\n", item->name, currentDungeon->name);
            }
        }

        // 3. Asignar ítem que derrota la mazmorra
        if (currentDungeon->id == 0)
        {
            // La primera mazmorra se derrota con el ítem que se compra en la tienda
            ItemPtr firstItem = items; // El primer ítem es el que se compra
            currentDungeon->requiredItem = firstItem;
            firstItem->defeats = currentDungeon;
            printf("Mazmorra %s se derrota con el ítem %s (comprado)\n",
                   currentDungeon->name, firstItem->name);
        }
        else
        {
            // Asignar un ítem al azar para derrotar la mazmorra
            bool itemAssigned = false;
            ItemPtr item = items;

            while (!itemAssigned)
            {
                while (item != NULL)
                {
                    // Si el ítem ya está asignado para derrotar una mazmorra, se salta
                    if (item->defeats != NULL)
                    {
                        item = item->next;
                        continue;
                    }

                    // Si el número es par, se asigna a esta mazmorra
                    if (rand() % 2 == 0)
                    {
                        currentDungeon->requiredItem = item;
                        item->defeats = currentDungeon;
                        itemAssigned = true;
                        printf("Mazmorra %s se derrota con el ítem %s\n",
                               currentDungeon->name, item->name);
                        break;
                    }

                    item = item->next;
                }

                // Si llegamos al final de la lista y no se asignó ítem, volvemos al principio
                // y asignamos el primer ítem disponible
                if (!itemAssigned)
                {
                    item = items;
                    while (item != NULL)
                    {
                        if (item->defeats == NULL)
                        {
                            currentDungeon->requiredItem = item;
                            item->defeats = currentDungeon;
                            itemAssigned = true;
                            printf("Mazmorra %s se derrota con el ítem %s (asignación forzada)\n",
                                   currentDungeon->name, item->name);
                            break;
                        }
                        item = item->next;
                    }
                }
            }
        }

        currentVillage = currentVillage->next;
    }
}
