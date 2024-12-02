/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <stdlib.h>
#include <unistd.h>

int get_time(tf_t *tf, int i, char *line)
{
    tf->pf[i].time.sec = tf->uptime - (double)atoll(get_value_tok(line, 21)) /
        sysconf(_SC_CLK_TCK);
    tf->pf[i].time.min = tf->pf[i].time.sec / 60;
    tf->pf[i].time.int_sec = (int)tf->pf[i].time.sec % 60;
    tf->pf[i].time.cent = (int)(tf->pf[i].time.sec * 100) % 100;
    return TOP_SUCCESS;
}
