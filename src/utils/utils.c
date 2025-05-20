#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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