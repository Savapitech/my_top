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
#include <unistd.h>

int get_virt(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 22; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].virt = atoll(p);
    return TOP_SUCCESS;
}

int get_pr(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 17; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].pr = atoi(p);
    return TOP_SUCCESS;
}

int get_ni(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 18; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].ni = atoi(p);
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
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 21; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].time = atoll(p);
    return TOP_SUCCESS;
}
