#ifndef DUNGEON_H
#define DUNGEON_H

typedef struct Dungeon
{
    char name[50];
    int defeated;                      // 0 = no, 1 = sí
    struct Item *requiredItem;         // Ítem necesario para derrotar
    struct Item *hiddenItem;           // Ítem oculto en esta mazmorra (puede ser NULL)
    struct Village *associatedVillage; // Aldea asociada a esta mazmorra
    struct Dungeon *next;
} Dungeon;

#endif // DUNGEON_H