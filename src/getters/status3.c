/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "top.h"

const char *get_value_tok(char *line, int skip)
{
    char const *s = line;
    size_t length;

    for (; skip > 0; skip--) {
        s += strcspn(s, " ");
        s += strspn(s, " ");
    }
    length = strcspn(s, " ");
    line = malloc((length + 1) * sizeof *line);
    if (line == NULL)
        return NULL;
    memcpy(line, s, length);
    line[length] = '\0';
    return line;
}

int get_time(tf_t *tf, int i, char *line)
{
    char const *toks[] = {
        get_value_tok(line, 21),
        get_value_tok(line, 13),
        get_value_tok(line, 14)
    };

    tf->pf[i].time.sec = tf->uptime - (double)atoll(toks[0]) /
        sysconf(_SC_CLK_TCK);
    tf->pf[i].time.min = tf->pf[i].time.sec / 60;
    tf->pf[i].time.int_sec = (int)tf->pf[i].time.sec % 60;
    tf->pf[i].time.cent = (int)(tf->pf[i].time.sec * 100) % 100;
    tf->pf[i].time.utime = atol(toks[1]);
    tf->pf[i].time.stime = atol(toks[2]);
    tf->pf[i].cpu = 100 * ((tf->pf[i].time.utime + tf->pf[i].time.stime) /
        (double)sysconf(_SC_CLK_TCK)) / tf->pf[i].time.sec;
    tf->pf_len.cpu = floatlen(tf->pf[i].cpu, 3) > tf->pf_len.cpu ?
        floatlen(tf->pf[i].cpu, 3) : tf->pf_len.cpu;
    return TOP_SUCCESS;
}
