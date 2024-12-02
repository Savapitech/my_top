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

const void *get_value_tok(char *line, int skip)
{
    char buff[strlen(line) + 1];
    void *p = NULL;

    strcpy(buff, line);
    p = strtok(buff, " ");
    for (int ii = 0; ii < skip; ii++)
        p = strtok(NULL, " ");
    return p;
}

int get_time(tf_t *tf, int i, char *line)
{
    tf->pf[i].time.sec = tf->uptime - (double)atoll(get_value_tok(line, 21)) /
        sysconf(_SC_CLK_TCK);
    tf->pf[i].time.min = tf->pf[i].time.sec / 60;
    tf->pf[i].time.int_sec = (int)tf->pf[i].time.sec % 60;
    tf->pf[i].time.cent = (int)(tf->pf[i].time.sec * 100) % 100;
    tf->pf[i].time.utime = atol(get_value_tok(line, 13));
    tf->pf[i].time.stime = atol(get_value_tok(line, 14));
    tf->pf[i].cpu = 100 * ((tf->pf[i].time.utime + tf->pf[i].time.stime) /
        (double)sysconf(_SC_CLK_TCK)) / tf->pf[i].time.sec;
    tf->pf_len.cpu = floatlen(tf->pf[i].cpu, 3) > tf->pf_len.cpu ?
        floatlen(tf->pf[i].cpu, 3) : tf->pf_len.cpu;
    return TOP_SUCCESS;
}
