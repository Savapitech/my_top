/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

int init_ncurses(tf_t *tf)
{
    int frames = 0;
    time_t tm;
    char *st;

    initscr();
    while (1) {
        clear();
        get_load_avg(tf);
        get_uptime(tf);
        tm = time(NULL);
        st = ctime(&tm);
        st += 11;
        printw("top - %.8s", st);
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
