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
    double proc_time;

    for (int i = 0; i < tf->processes.total && i < tf->winsize->ws_row - 4;
        i++) {
        if (tf->pf[i].pid) {
            proc_time = tf->uptime - (double)tf->pf[i].time /
                sysconf(_SC_CLK_TCK);
            printw("%*d %*s %*d %*d %*lld %*lld             %1c   %f %s\n",
                tf->pf_len.pid, tf->pf[i].pid, tf->pf_len.uid,
                getpwuid(tf->pf[i].uid)->pw_name, tf->pf_len.pr, tf->pf[i].pr,
                tf->pf_len.ni, tf->pf[i].ni, tf->pf_len.virt, tf->pf[i].virt,
                tf->pf_len.res, tf->pf[i].res, tf->pf[i].state, proc_time,
                tf->pf[i].cmd);
        }
    }
}

static
void print_proc_header(tf_t *tf)
{
    attron(COLOR_PAIR(BLACK_ON_WHITE));
    printw("\n\n%*sPID %*sUSER %*sPR %*sNI %*sVIRT %*sRES %*sSHR S %*s%%CPU ",
            tf->pf_len.pid - 3, "", tf->pf_len.uid - 4, "", tf->pf_len.pr - 2,
            "", tf->pf_len.ni - 2, "", tf->pf_len.virt - 4, "",
            tf->pf_len.res - 3, "", tf->pf_len.shr - 3, "", tf->pf_len.cpu - 4,
            "");
    printw("%*s%%MEM %*sTIME+ COMMAND %*c", tf->pf_len.mem - 4, "",
            tf->pf_len.time - 5, "", tf->winsize->ws_col - (86 +
            (tf->pf_len.pid - 3 + tf->pf_len.uid - 4 + tf->pf_len.pr - 2 +
            tf->pf_len.ni - 2 + tf->pf_len.virt - 4 + tf->pf_len.res - 3 +
            tf->pf_len.shr - 3 + tf->pf_len.cpu - 4 + tf->pf_len.mem - 4 +
            tf->pf_len.time - 5)), ' ');
    attroff(COLOR_PAIR(BLACK_ON_WHITE));
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
    printw("Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie",
        tf->processes.total, tf->processes.running, tf->processes.sleeping,
        tf->processes.stopped, tf->processes.zombie);
    print_proc_header(tf);
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
