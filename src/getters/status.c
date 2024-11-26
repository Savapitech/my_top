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
    p[strlen(p) - 1] = '\0';
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
    return TOP_SUCCESS;
}

int get_state(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "State:", 6) != 0)
        return TOP_FAILURE;
    p = line + 7;
    while (isspace(*p))
        ++p;
    tf->pf[i].state = *p;
    return TOP_SUCCESS;
}

int get_uid(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "Uid:", 4) != 0)
        return TOP_FAILURE;
    p = line + 5;
    while (isspace(*p))
        ++p;
    tf->pf[i].uid = atoi(p);
    return TOP_SUCCESS;
}

int get_gid(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "Gid:", 4) != 0)
        return TOP_FAILURE;
    p = line + 5;
    while (isspace(*p))
        ++p;
    tf->pf[i].gid = atoi(p);
    return TOP_SUCCESS;
}
