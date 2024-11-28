/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <ctype.h>
#include <grp.h>
#include <pwd.h>
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
    tf->pf_len.cmd = (int)strlen(tf->pf[i].cmd) > tf->pf_len.cmd ?
        strlen(tf->pf[i].cmd) : tf->pf_len.cmd;
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

static
void count_processes_state(tf_t *tf, int i)
{
    switch (tf->pf[i].state) {
        case 'R':
            tf->processes.running++;
            break;
        case 'S':
        case 'I':
            tf->processes.sleeping++;
            break;
        case 'T':
            tf->processes.stopped++;
            break;
        case 'Z':
            tf->processes.zombie++;
            break;
    }
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
    count_processes_state(tf, i);
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
    tf->pf_len.uid = (int)strlen(getpwuid(tf->pf[i].uid)->pw_name) >
        tf->pf_len.uid ? strlen(getpwuid(tf->pf[i].uid)->pw_name) :
        tf->pf_len.uid;
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
    tf->pf_len.gid = (int)strlen(getgrgid(tf->pf[i].gid)->gr_name) >
        tf->pf_len.gid ? strlen(getgrgid(tf->pf[i].gid)->gr_name) :
        tf->pf_len.gid;
    return TOP_SUCCESS;
}
