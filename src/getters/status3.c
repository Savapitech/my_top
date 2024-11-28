/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_time(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 21; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].time = atoll(p);
    return TOP_SUCCESS;
}
