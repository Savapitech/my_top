/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <ncurses.h>

void print_uptime(tf_t *tf)
{
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;

    printw(" up %ld days, %02ld:%02ld:%02ld,", (long)tf->uptime / day,
        ((long)tf->uptime % day) / hour, ((long)tf->uptime % hour) / minute,
        (long)tf->uptime % minute);
}
