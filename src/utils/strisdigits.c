/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include <ctype.h>

int strisdigits(char *str)
{
    for (char *p = str; *p != '\0'; p++)
        if (!isdigit(*p))
            return 0;
    return 1;
}
