#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils/utils.h"

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

    return atoi(input);
}