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
        get_proc_list(tf);
        print_time();
        print_uptime(tf);
        printw(" load average: %.2f, %.2f, %.2f\n", tf->lavg.one_m,
            tf->lavg.five_m, tf->lavg.fifteen_m);
            printw("Tasks: %3d total, ", tf->processes.total);
        frames++;
        refresh();
        sleep(1);
    }
    endwin();
    return TOP_SUCCESS;
}
