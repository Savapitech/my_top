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

int get_pr(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 17; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].pr = atoi(p);
    tf->pf_len.pr = intlen(tf->pf[i].pr) > tf->pf_len.pr ?
        intlen(tf->pf[i].pr) : tf->pf_len.pr;
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
    tf->pf_len.ni = intlen(tf->pf[i].ni) > tf->pf_len.ni ?
        intlen(tf->pf[i].ni) : tf->pf_len.ni;
    return TOP_SUCCESS;
}

int get_virt(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 22; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].virt = atoll(p);
    tf->pf_len.virt = intlen(tf->pf[i].virt) > tf->pf_len.virt ?
        intlen(tf->pf[i].virt) : tf->pf_len.virt;
    return TOP_SUCCESS;
}

int get_res(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    for (int ii = 0; ii < 23; ii++)
        p = strtok(NULL, " ");
    tf->pf[i].res = atoll(p);
    tf->pf_len.res = intlen(tf->pf[i].res) > tf->pf_len.res ?
        intlen(tf->pf[i].res) : tf->pf_len.res;
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
