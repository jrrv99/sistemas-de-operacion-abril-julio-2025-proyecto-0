#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

/**
 * Reads a line of input from stdin with dynamic memory allocation
 * @return Dynamically allocated string containing the input line, or NULL on error
 */
char *read_line()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);
    if (read == -1)
    {
        free(line);
        return NULL;
    }

    if (read > 0 && line[read - 1] == '\n')
    {
        line[read - 1] = '\0';
    }

    return line;
}

bool is_number(const char *str)
{
    if (str == NULL || *str == '\0')
    {
        return false; // Cadena vacía o nula
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return false; // Encontrado un carácter no numérico
        }
    }

    return true;
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int random_int(int min, int max)
{
    assert(min <= max && "Error: min should be less than or equal to max\n");

    int range = max - min + 1;

    return min + (rand() % range);
}

char *generateName(
    const char **typeArray, int typeCount,
    const char **nameArray, int nameCount,
    int salt)
{
    assert(typeCount > 0 && nameCount > 0 && "Arrays cannot be empty");

    // Escoge tipo aleatorio
    const char *type = typeArray[random_int(0, typeCount - 1)];

    // Determinar cuántos elementos vamos a combinar (sin tope artificial)
    int combinationSize = 1 + (salt / nameCount);

    // Calcular el tamaño necesario
    int estimatedLen = strlen(type) + strlen(" de ") + 1;
    for (int i = 0; i < combinationSize; i++)
    {
        const char *element = nameArray[(salt + i) % nameCount];
        estimatedLen += strlen(element) + 1; // +1 por '-' o '\0'
    }

    // Reservar memoria
    char *name = malloc(estimatedLen);
    if (!name)
    {
        perror("Error: failed to allocate memory for name");
        exit(EXIT_FAILURE);
    }

    snprintf(name, estimatedLen, "%s de ", type);

    // agregar partes: "Fuego-Agua-..." para formar el nombre completo: "Espada de Fuego-Agua-..."
    for (int i = 0; i < combinationSize; i++)
    {
        const char *element = nameArray[(salt + i) % nameCount];
        strcat(name, element);
        if (i < combinationSize - 1)
            strcat(name, "-");
    }

    return name;
}
