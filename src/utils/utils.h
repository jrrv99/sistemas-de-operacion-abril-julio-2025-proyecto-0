#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

char *read_line(void);
bool is_number(const char *str);
void clear_screen(void);
int random_int(int min, int max);
char *generateName(
    const char **typeArray, int typeCount,
    const char **nameArray, int nameCount,
    int index);
void pause(const char *message);

#endif // UTILS_H