/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <ncurses.h>
#include <unistd.h>

int init_ncurses(tf_t *tf)
{
    int frames = 0;

    initscr();
    while (1) {
        clear();
        get_load_avg(tf);
        get_uptime(tf);
        print_time();
        print_uptime(tf);
        printw(" load average: %.2f, %.2f, %.2f", tf->lavg.one_m,
            tf->lavg.five_m, tf->lavg.fifteen_m);
        frames++;
        refresh();
        sleep(1);
    }
    endwin();
    return TOP_SUCCESS;
}
