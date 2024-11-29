/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include <ctype.h>

__attribute__((const))
int strisdigits(char *str)
{
    for (char *p = str; *p != '\0'; p++)
        if (!isdigit(*p))
            return 0;
    return 1;
}
