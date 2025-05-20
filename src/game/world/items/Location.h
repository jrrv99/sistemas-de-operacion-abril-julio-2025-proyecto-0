#ifndef LOCATION_H
#define LOCATION_H

typedef enum LocationType
{
    LOCATION_SHOP,    // Tienda (comprable)
    LOCATION_DUNGEON, // Mazmorras
    LOCATION_VILLAGE, // Aldea
} LocationType;

typedef union LocationData
{
    void *shop;              // Tienda
    struct Dungeon *dungeon; // Mazmorras
    struct Village *village; // Aldea
} LocationData;

typedef struct Location
{
    LocationType type; // Tipo de localización
    LocationData place;

} Location;

typedef struct Location *LocationPtr;

LocationPtr createLocation(LocationType type, void *place);
LocationPtr createShopLocation(void);
LocationPtr createDungeonLocation(struct Dungeon *dungeon);
LocationPtr createVillageLocation(struct Village *village);

#endif // LOCATION_H