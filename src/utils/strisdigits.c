/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include <ctype.h>
#include <string.h>

__attribute__((const))
int strisstr(char *str)
{
    for (char *p = str; *p != '\0'; p++)
        if (!isalpha(*p) && !ispunct(*p))
            return 0;
    return 1;
}

__attribute__((const))
int strisdigits(char *str)
{
    for (char *p = str; *p != '\0'; p++)
        if (!isdigit(*p))
            return 0;
    return 1;
}

__attribute__((const))
int strisfloat(char *str)
{
    int points = 0;
    char *p = str;

    if (*p == '.')
        return 0;
    if (p[strlen(p)] == '.')
        return 0;
    for (; *p != '\0'; p++) {
        if (*p == '.')
            points++;
        if (!isdigit(*p) && *p != '.' && points > 1)
            return 0;
    }
    return 1;
}
