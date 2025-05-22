#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../utils/utils.h"
#include "world/world.h"
#include "player/Player.h"

#include "game.h"

int readNumOfVillages()
{
    char *input = NULL;
    bool valid = true;

    do
    {
        if (!valid)
        {
            clear_screen();
            printf("Invalid input %s. Please enter a valid number.\n", input);
        }

        printf("Enter the number of villages: ");

        input = read_line();

        valid = is_number(input);
    } while (!valid);

    int result = atoi(input);
    free(input);
    return result;
}

/**
 * Inicializa el mundo superior del juego con un número dado de aldeas.
 * El mundo paralelo se carga cuando se desbloquea.
 */
GameStatePtr initialize_game(int numOfVillages)
{
    GameStatePtr game = malloc(sizeof(*game));

    if (game == NULL)
    {
        perror("Error allocating memory for game state\n");
        exit(EXIT_FAILURE);
    }

    game->upperWorld = createWorld(numOfVillages, false, NULL);
    game->player = createPlayer(game->upperWorld->villages);
    game->parallelWorld = NULL;
    game->parallelWorldUnlocked = false;
    game->villagesToDefeatToUnlock = random_int(1, numOfVillages);

    return game;
}

/**
 * Muestra el menú de compra en una aldea
 */
void shop_menu(GameStatePtr game)
{
    printf("\n=== TIENDA ===\n");
    printf("1. Recuperar vida - $5\n");
    printf("2. Ítem para primera mazmorra - $25\n");
    printf("3. Vida adicional - $100\n");
    printf("0. Salir\n");

    char *input = NULL;
    int option = -1;
    bool valid = false;

    do
    {
        printf("Selecciona una opción: ");
        input = read_line();

        if (input == NULL)
        {
            continue;
        }

        if (is_number(input))
        {
            option = atoi(input);
            valid = true;
        }
        else
        {
            printf("Opción inválida. Ingrese un número.\n");
        }

        free(input);
    } while (!valid);

    switch (option)
    {
    case 1:
        if (game->player->money < 5)
        {
            printf("No tienes suficiente dinero para recuperar vidas.\n");
            return;
        }

        if (game->player->lives >= game->player->maxLives)
        {
            printf("Tienes mas de %d vidas. No necesitas recuperar vidas\n", INIT_LIVES);
            return;
        }

        game->player->lives = game->player->maxLives;
        game->player->money -= 5;
        printf("¡Vida recuperada!\n");

        break;
    case 2:
        if (game->player->money < 25)
        {
            printf("No tienes suficiente dinero.\n");
            return;
        }

        // Marcar el primer ítem como encontrado
        ItemPtr firstItem = game->upperWorld->items;

        if (firstItem != NULL && firstItem->locationType == LOCATION_SHOP)
        {
            firstItem->found = true;
            game->player->money -= 25;
            printf("¡Has comprado %s!\n", firstItem->name);
        }
        else
        {
            printf("Error: No se encontró el ítem de la tienda.\n");
        }

        break;
    case 3:
        if (game->player->money < 100)
        {
            printf("No tienes suficiente dinero.\n");
            return;
        }

        if (game->player->maxLives >= MAX_LIVES)
        {
            printf("Ya has alcanzado el máximo de vidas posible.\n");
            return;
        }

        game->player->maxLives++;
        game->player->lives = game->player->maxLives;
        game->player->money -= 100;
        printf("¡Vida aumentada a %d!\n", game->player->maxLives);

        break;
    case 0:
        printf("Vuelve pronto.\n");
        break;
    default:
        printf("Opción inválida.\n");
    }
}

/**
 * Procesa el movimiento entre ubicaciones
 */
void move_player(GameStatePtr game, VillagePtr destination)
{
    if (destination == NULL)
    {
        printf("No puedes ir en esa dirección.\n");
        return;
    }

    // Encontrar dinero en el camino
    game->player->money += 10;
    printf("Te diriges a %s. Encuentras $10 en el camino.\n", destination->name);

    // Posibilidad de perder vida en el camino
    if (rand() % 4 == 0)
    { // 25% de probabilidad
        game->player->lives--;
        printf("¡Te atacaron en el camino! Pierdes una vida.\n");
    }

    game->player->currentLocation = destination;
}

/**
 * Función principal del juego
 */
void play()
{
    clear_screen();
    printf("¡Bienvenido a Zelda Rogue!\n\n");

    int numOfVillages = readNumOfVillages();
    GameStatePtr game = initialize_game(numOfVillages);

    printf("\nDebes derrotar %d mazmorras para desbloquear el mundo paralelo.\n",
           game->villagesToDefeatToUnlock);
    pause("Presiona Enter para continuar...");

    bool gameOver = false;
    bool inDungeon = false;

    while (!gameOver)
    {
        clear_screen();

        // Verificar si el jugador ha perdido todas las vidas
        if (game->player->lives <= 0)
        {
            printf("\n*** GAME OVER ***\n");
            printf("Te has quedado sin vidas.\n");
            break;
        }

        // Obtener la ubicación actual
        VillagePtr currentVillage = game->player->currentLocation;
        DungeonPtr currentDungeon = NULL;

        if (inDungeon)
        {
            currentDungeon = currentVillage->associatedDungeon;
            printf("\n=== MAZMORRA: %s ===\n", currentDungeon->name);
        }
        else
        {
            printf("\n=== ALDEA: %s ===\n", currentVillage->name);
        }

        // Mostrar información del jugador
        printf("Vidas: %d/%d | Dinero: $%d\n",
               game->player->lives, game->player->maxLives, game->player->money);

        // Mostrar información del mundo
        if (game->upperWorld->isParallel)
        {
            printf("Mundo: Paralelo | ");
        }
        else
        {
            printf("Mundo: Superior | ");
        }

        printf("Mazmorras derrotadas: %d/%d\n",
               game->upperWorld->defeatedDungeons,
               game->villagesToDefeatToUnlock);

        if (game->parallelWorldUnlocked)
        {
            printf("Mundo paralelo desbloqueado");
            if (game->player->canTravelBetweenWorlds)
            {
                printf(" | Viaje entre mundos disponible");
            }
            printf("\n");
        }

        // Calcular el número total de mazmorras
        int totalDungeons = game->upperWorld->numOfVillages * 2;
        int defeatedDungeons = game->upperWorld->defeatedDungeons;
        if (game->parallelWorld != NULL)
        {
            defeatedDungeons += game->parallelWorld->defeatedDungeons;
        }
        int remainingDungeons = totalDungeons - defeatedDungeons;

        printf("Mazmorras restantes para ganar: %d\n", remainingDungeons);

        // Mostrar prompt y leer comando
        printf("\n> ");
        char *command = read_line();

        if (command == NULL)
        {
            continue;
        }

        // Procesar comando
        if (inDungeon)
        {
            // Comandos en mazmorra
            if (strcmp(command, "busq") == 0)
            {
                search_dungeon(game, currentDungeon);
            }
            else if (strcmp(command, "atac") == 0)
            {
                bool gameCompleted = attack_dungeon(game, currentDungeon);
                if (gameCompleted)
                {
                    gameOver = true;
                }
            }
            else if (strcmp(command, "ant") == 0)
            {
                inDungeon = false;
                printf("Regresas a la aldea %s.\n", currentVillage->name);
            }
            else if (strcmp(command, "sig") == 0)
            {
                if (currentVillage->next != NULL)
                {
                    inDungeon = false;
                    move_player(game, currentVillage->next);
                }
                else
                {
                    printf("No hay más aldeas en esta dirección.\n");
                }
            }
            else
            {
                printf("Comando no reconocido. Comandos disponibles: busq, atac, ant, sig\n");
            }

            // Posibilidad de perder vida en la mazmorra
            if (rand() % 5 == 0)
            { // 20% de probabilidad
                game->player->lives--;
                printf("¡Un monstruo te ataca! Pierdes una vida. Vidas restantes: %d\n",
                       game->player->lives);
            }
        }
        else
        {
            // Comandos en aldea
            if (strcmp(command, "busq") == 0)
            {
                search_village(currentVillage);
            }
            else if (strcmp(command, "maz") == 0)
            {
                printf("Te diriges a la mazmorra %s...\n", currentVillage->associatedDungeon->name);
                inDungeon = true;
            }
            else if (strcmp(command, "compr") == 0)
            {
                shop_menu(game);
            }
            else if (strcmp(command, "trans") == 0)
            {
                if (game->parallelWorldUnlocked && game->player->canTravelBetweenWorlds)
                {
                    if (currentVillage->counterpart != NULL)
                    {
                        game->player->currentLocation = currentVillage->counterpart;
                        printf("Te has transportado al mundo %s.\n",
                               game->upperWorld->isParallel ? "superior" : "paralelo");
                    }
                    else
                    {
                        printf("Error: No hay aldea correspondiente en el otro mundo.\n");
                    }
                }
                else
                {
                    printf("Aún no puedes viajar entre mundos.\n");
                }
            }
            else if (strcmp(command, "ant") == 0)
            {
                if (currentVillage->previous != NULL)
                {
                    move_player(game, currentVillage->previous);
                }
                else
                {
                    printf("No puedes ir a la anterior, ¡aquí naciste!\n");
                }
            }
            else if (strcmp(command, "sig") == 0)
            {
                if (currentVillage->next != NULL)
                {
                    move_player(game, currentVillage->next);
                }
                else
                {
                    printf("No puedes ir a la siguiente, ¡este es el fin del mundo!\n");
                }
            }
            else
            {
                printf("Comando no reconocido. Comandos disponibles: busq, maz, compr, trans, ant, sig\n");
            }
        }

        free(command);

        pause("Presiona Enter para continuar...");
    }

    // Liberar memoria
    // TODO: Implementar funciones para liberar la memoria de game, worlds, etc.

    printf("\n¡Gracias por jugar Zelda Rogue!\n");
}