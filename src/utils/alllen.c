/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <stdio.h>
#include <string.h>

int floatlen(float value, int precision)
{
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "%.*f", precision, value);
    return (int)strlen(buffer);
}

int intlen(long long value)
{
    int length = (value < 0) ? 1 : 0;

    while (value != 0) {
        value /= 10;
        length++;
    }
    return (length == 0) ? 1 : length;
}
