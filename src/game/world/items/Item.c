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
    // Asegurarse de que la semilla aleatoria esté inicializada
    // (Esto debería hacerse una vez al inicio del programa, no aquí)

    VillagePtr currentVillage = villages;
    ItemPtr currentItem = items;

    // Primer ítem siempre va a la tienda y derrota la primera mazmorra
    if (currentItem != NULL && currentVillage != NULL)
    {
        DungeonPtr firstDungeon = currentVillage->associatedDungeon;

        // Asignar el primer ítem a la tienda
        currentItem->locationType = LOCATION_SHOP;
        currentItem->location = NULL; // La tienda no tiene una ubicación específica
        currentItem->found = false;

        // Este ítem derrota la primera mazmorra
        currentItem->defeats = firstDungeon;
        firstDungeon->requiredItem = currentItem;

        printf("Ítem %s asignado a la tienda y derrota la mazmorra %s\n",
               currentItem->name, firstDungeon->name);

        // Avanzar al siguiente ítem
        currentItem = currentItem->next;
    }

    // Recorrer todas las aldeas
    while (currentVillage != NULL)
    {
        // Para cada aldea, generar un número aleatorio
        if (rand() % 2 == 0 && currentItem != NULL)
        { // Si es par
            // Asignar un ítem a esta aldea
            currentVillage->hiddenItem = currentItem;
            currentItem->locationType = LOCATION_VILLAGE;
            currentItem->location = currentVillage;
            currentItem->found = false;

            printf("Ítem %s asignado a la aldea %s\n",
                   currentItem->name, currentVillage->name);

            // Avanzar al siguiente ítem
            currentItem = currentItem->next;
        }

        // Obtener la mazmorra asociada a esta aldea
        DungeonPtr currentDungeon = currentVillage->associatedDungeon;

        // Para cada mazmorra, generar un número aleatorio
        if (currentDungeon != NULL && currentDungeon->id > 0)
        { // Saltamos la primera mazmorra (ya asignada)
            // Para la mazmorra, generar un número aleatorio
            if (rand() % 2 == 0 && currentItem != NULL)
            { // Si es par
                // Asignar un ítem a esta mazmorra
                currentDungeon->hiddenItem = currentItem;
                currentItem->locationType = LOCATION_DUNGEON;
                currentItem->location = currentDungeon;
                currentItem->found = false;

                printf("Ítem %s asignado a la mazmorra %s\n",
                       currentItem->name, currentDungeon->name);

                // Avanzar al siguiente ítem
                currentItem = currentItem->next;
            }

            // Asignar a la mazmorra el ítem que la derrota (si no es la primera)
            if (currentDungeon->id > 0)
            {
                // Recorrer la lista de ítems para asignarle uno al azar
                bool itemAssigned = false;
                ItemPtr itemCursor = items;

                while (!itemAssigned)
                {
                    while (itemCursor != NULL)
                    {
                        // Si el ítem ya está asignado para derrotar una mazmorra, se salta
                        if (itemCursor->defeats != NULL)
                        {
                            itemCursor = itemCursor->next;
                            continue;
                        }

                        // Si el número aleatorio es par, se asigna a esa mazmorra
                        if (rand() % 2 == 0)
                        {
                            currentDungeon->requiredItem = itemCursor;
                            itemCursor->defeats = currentDungeon;
                            itemAssigned = true;

                            printf("Mazmorra %s se derrota con el ítem %s\n",
                                   currentDungeon->name, itemCursor->name);
                            break;
                        }

                        itemCursor = itemCursor->next;
                    }

                    // Si se llega al final de la lista de ítems sin asignar,
                    // volver a comenzar y asignar el primer ítem disponible
                    if (!itemAssigned)
                    {
                        itemCursor = items;
                        while (itemCursor != NULL)
                        {
                            if (itemCursor->defeats == NULL)
                            {
                                currentDungeon->requiredItem = itemCursor;
                                itemCursor->defeats = currentDungeon;
                                itemAssigned = true;

                                printf("Mazmorra %s se derrota con el ítem %s (asignación forzada)\n",
                                       currentDungeon->name, itemCursor->name);
                                break;
                            }
                            itemCursor = itemCursor->next;
                        }
                    }
                }
            }
        }

        // Avanzar a la siguiente aldea
        currentVillage = currentVillage->next;
    }

    // PASO FINAL: Forzar la asignación de ítems que no fueron asignados a ninguna ubicación
    // (excepto el primer ítem que va a la tienda)
    ItemPtr item = items->next; // Empezamos desde el segundo ítem
    while (item != NULL)
    {
        // Si el ítem no tiene ubicación y no está en la tienda
        if (item->location == NULL && item->locationType != LOCATION_SHOP)
        {
            // Primero intentamos asignarlo a una aldea sin ítem
            VillagePtr v = villages;
            bool assigned = false;

            // Buscar una aldea sin ítem oculto
            while (v != NULL && !assigned)
            {
                if (v->hiddenItem == NULL)
                {
                    v->hiddenItem = item;
                    item->locationType = LOCATION_VILLAGE;
                    item->location = v;
                    item->found = false;
                    assigned = true;
                    printf("Ítem %s asignado forzadamente a la aldea %s\n",
                           item->name, v->name);
                }
                v = v->next;
            }

            // Si no encontramos aldea, buscamos una mazmorra sin ítem
            if (!assigned)
            {
                v = villages;
                while (v != NULL && !assigned)
                {
                    DungeonPtr d = v->associatedDungeon;
                    if (d != NULL && d->hiddenItem == NULL && d->id > 0)
                    { // Saltamos la primera mazmorra
                        d->hiddenItem = item;
                        item->locationType = LOCATION_DUNGEON;
                        item->location = d;
                        item->found = false;
                        assigned = true;
                        printf("Ítem %s asignado forzadamente a la mazmorra %s\n",
                               item->name, d->name);
                    }
                    v = v->next;
                }
            }

            // Si aún no se pudo asignar (todas las ubicaciones tienen ítems),
            // lo asignamos a la primera aldea (puede tener más de un ítem)
            if (!assigned)
            {
                villages->hiddenItem = item;
                item->locationType = LOCATION_VILLAGE;
                item->location = villages;
                item->found = false;
                printf("Ítem %s asignado forzadamente a la aldea %s (ya tenía ítem)\n",
                       item->name, villages->name);
            }
        }
        item = item->next;
    }
}