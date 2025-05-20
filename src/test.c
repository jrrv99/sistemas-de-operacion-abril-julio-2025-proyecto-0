#include "utils/utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *input;

    do
    {
        printf("Enter a number: ");
        input = read_line();
    } while (!isdigit(*input));
    
    
    return 0;
}
