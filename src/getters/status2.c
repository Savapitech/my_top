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

int get_virt(tf_t *tf, int i, char *line)
{
    char *line2 = line;
    char *p;

    p = strtok(line2, " ");
    for (int ii = 0; ii < 22; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].virt = atoll(p);
    return TOP_SUCCESS;
}

int get_pr(tf_t *tf, int i, char *line)
{
    char *line2 = line;
    char *p;

    p = strtok(line2, " ");
    for (int ii = 0; ii < 16; ii++)
        p = strtok(NULL, " ");
    //tf->pf[i].pr = atoi(p);
    return TOP_SUCCESS;
}

int get_res(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "State:", 6) != 0) {
        tf->pf[i].res = 0;
        return TOP_FAILURE;
    }
    p = line + 7;
    while (isspace(*p))
        ++p;
    tf->pf[i].state = *p;
    return TOP_SUCCESS;
}

int get_shr(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "State:", 6) != 0) {
        tf->pf[i].shr = 0;
        return TOP_FAILURE;
    }
    p = line + 7;
    while (isspace(*p))
        ++p;
    tf->pf[i].state = *p;
    return TOP_SUCCESS;
}

int get_time(tf_t *tf, int i, char *line)
{
    char *p;

    if (strncmp(line, "State:", 6) != 0) {
        tf->pf[i].time = 0;
        return TOP_FAILURE;
    }
    p = line + 7;
    while (isspace(*p))
        ++p;
    tf->pf[i].state = *p;
    return TOP_SUCCESS;
}
