#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils/utils.h"

int readNumOfVillages()
{
    char *input = NULL;
    bool valid = false;

    do
    {
        clear_screen();

        if (input != NULL)
        {
            printf("Entrada inválida. Por favor ingrese un número válido.\n");
            free(input);
        }

        printf("Ingrese el número de aldeas a generar: ");
        input = read_line();

        if (input == NULL)
        {
            continue;
        }

        valid = is_number(input);
        if (valid)
        {
            int num = atoi(input);
            if (num <= 0)
            {
                valid = false;
            }
        }
    } while (!valid);

    int result = atoi(input);
    free(input);
    return result;
}
