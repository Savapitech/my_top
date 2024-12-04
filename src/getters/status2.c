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
    char const *tok = get_value_tok_or_zero(line, 17);

    tf->pf[i].pr = atoi(tok);
    tf->pf_len.pr = intlen(tf->pf[i].pr) > tf->pf_len.pr ?
        intlen(tf->pf[i].pr) : tf->pf_len.pr;
    free((void *)tok);
    return TOP_SUCCESS;
}

int get_ni(tf_t *tf, int i, char *line)
{
    char const *tok = get_value_tok_or_zero(line, 18);

    tf->pf[i].ni = atoi(tok);
    tf->pf_len.ni = intlen(tf->pf[i].ni) > tf->pf_len.ni ?
        intlen(tf->pf[i].ni) : tf->pf_len.ni;
    free((void *)tok);
    return TOP_SUCCESS;
}

int get_virt(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    tf->pf[i].virt = atoll(p) * getpagesize() / 1024;
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
    p = strtok(NULL, " ");
    tf->pf[i].res = atoll(p) * getpagesize() / 1024;
    tf->pf_len.res = intlen(tf->pf[i].res) > tf->pf_len.res ?
        intlen(tf->pf[i].res) : tf->pf_len.res;
    return TOP_SUCCESS;
}

int get_shr(tf_t *tf, int i, char *line)
{
    char line2[400];
    char *p;

    strcpy(line2, line);
    p = strtok(line2, " ");
    p = strtok(NULL, " ");
    p = strtok(NULL, " ");
    tf->pf[i].shr = atoll(p) * getpagesize() / 1024;
    tf->pf_len.shr = intlen(tf->pf[i].shr) > tf->pf_len.shr ?
        intlen(tf->pf[i].shr) : tf->pf_len.shr;
    return TOP_SUCCESS;
}
