/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int get_name(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "Name:", 5) != 0)
        return TOP_FAILURE;
    p = line + 6;
    while (isspace(*p))
        ++p;
    tf->pf[i].cmd = strdup(p);
    return TOP_SUCCESS;
}

int get_pid(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "Pid:", 4) != 0)
        return TOP_FAILURE;
    p = line + 5;
    while (isspace(*p))
        ++p;
    tf->pf[i].pid = atoi(p);
    printw("PID: %d ", tf->pf[i].pid);
    return TOP_SUCCESS;
}
