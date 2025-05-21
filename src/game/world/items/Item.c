#include <stdlib.h>
#include <stdio.h>

#include "../../../utils/utils.h"
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