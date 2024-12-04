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

static char const ZERO[] = "0";

const char *get_value_tok_or_zero(char const *line, int skip)
{
    char *out;
    char const *s = line;
    size_t length;

    for (; skip > 0; skip--) {
        s += strcspn(s, " ");
        s += strspn(s, " ");
    }
    length = strcspn(s, " ");
    out = malloc((length + 1) * sizeof *out);
    if (out == NULL)
        return ZERO;
    memcpy(out, s, length);
    out[length] = '\0';
    return out;
}

static
void calc_time(tf_t *tf, int i)
{
    tf->pf[i].time.su_time_sec = (double)tf->pf[i].time.utime /
        sysconf(_SC_CLK_TCK) + (double)tf->pf[i].time.stime /
        sysconf(_SC_CLK_TCK);
    tf->pf[i].time.min = tf->pf[i].time.su_time_sec / 60;
    tf->pf[i].time.int_sec = (int)tf->pf[i].time.su_time_sec % 60;
    tf->pf[i].time.cent = (int)(tf->pf[i].time.su_time_sec * 100) % 100;
    tf->pf[i].cpu = 100 * ((tf->pf[i].time.utime + tf->pf[i].time.stime) /
        (double)sysconf(_SC_CLK_TCK)) / tf->pf[i].time.sec;
}

int get_time(tf_t *tf, int i, char *line)
{
    int idx[] = { 21, 13, 14 };
    char const *toks[ARRAY_SIZE(idx)];

    for (size_t i = 0; i < ARRAY_SIZE(toks); i++)
        toks[i] = get_value_tok_or_zero(line, idx[i]);
    tf->pf[i].time.sec = tf->uptime - (double)atoll(toks[0]) /
        sysconf(_SC_CLK_TCK);
    tf->pf[i].time.utime = atol(toks[1]);
    tf->pf[i].time.stime = atol(toks[2]);
    calc_time(tf, i);
    tf->pf_len.cpu = floatlen(tf->pf[i].cpu, 3) > tf->pf_len.cpu ?
        floatlen(tf->pf[i].cpu, 3) : tf->pf_len.cpu;
    for (size_t i = 0; i < ARRAY_SIZE(toks); i++)
        if (toks[i] != ZERO)
            free((void *)toks[i]);
    return TOP_SUCCESS;
}
