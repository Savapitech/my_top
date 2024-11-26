/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <ncurses.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

static
void print_procs(tf_t *tf)
{
    for (int i = 0; i < tf->processes.total && i < tf->winsize->ws_row - 4;
        i++) {
        if (tf->pf[i].pid)
            printw("%d %s %d %d %lld\n", tf->pf[i].pid,
                getpwuid(tf->pf[i].uid)->pw_name, tf->pf[i].pr, tf->pf[i].ni,
                tf->pf[i].virt);
    }
}

static
void printer(tf_t *tf)
{
    get_load_avg(tf);
    get_uptime(tf);
    get_proc_list(tf);
    print_time();
    print_uptime(tf);
    printw(" load average: %.2f, %.2f, %.2f\n", tf->lavg.one_m,
        tf->lavg.five_m, tf->lavg.fifteen_m);
    printw("Tasks: %3d total, ", tf->processes.total);
    attron(COLOR_PAIR(BLACK_ON_WHITE));
    printw("\n\n PID USER PR NI VIRT RES SHR S %%CPU %%MEM TIME+ COMMAND % *c",
        tf->winsize->ws_col - 55, ' ');
    attroff(COLOR_PAIR(BLACK_ON_WHITE));
}

int init_ncurses(tf_t *tf)
{
    struct winsize winsize;

    initscr();
    start_color();
    use_default_colors();
    curs_set(0);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
    tf->winsize = &winsize;
    while (1) {
        clear();
        ioctl(STDOUT_FILENO, TIOCGWINSZ, tf->winsize);
        printer(tf);
        print_procs(tf);
        refresh();
        sleep(1);
        if (tf->pf)
            free(tf->pf);
    }
    endwin();
    return TOP_SUCCESS;
}
