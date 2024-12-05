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
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static
void print_procs2(tf_t *tf, int i, char *username)
{
    printw("%*d %-*s %*d %*d %*lld %*lld %*lld",
            tf->pf_len.pid, tf->pf[i].pid, tf->pf_len.uid,
            username, tf->pf_len.pr, tf->pf[i].pr,
            tf->pf_len.ni, tf->pf[i].ni, tf->pf_len.virt, tf->pf[i].virt,
            tf->pf_len.res, tf->pf[i].res, tf->pf_len.shr, tf->pf[i].shr);
    printw(" %1c %*.1f %*.1f %d:%02d.%02d %s\n", tf->pf[i].state,
            tf->pf_len.cpu, tf->pf[i].cpu, tf->pf_len.mem, tf->pf[i].mem,
            tf->pf[i].time.min, tf->pf[i].time.int_sec,
            tf->pf[i].time.cent, tf->pf[i].cmd);
}

static
void print_procs(tf_t *tf)
{
    int displayed_i = 0;
    char *username = NULL;

    for (int i = tf->min_displayed_i; i < tf->processes.total &&
        displayed_i < tf->winsize->ws_row - 7; i++) {
        username = get_user_name(tf->pf[i].uid);
        if (tf->pf[i].pid && (!tf->user ||
            !strcmp(username, tf->user))) {
            print_procs2(tf, i, username);
            displayed_i++;
        }
        free(username);
    }
}

static
void print_proc_header(tf_t *tf)
{
    attron(COLOR_PAIR(BLACK_ON_WHITE));
    printw("\n\n%*sPID USER%*s %*sPR %*sNI %*sVIRT %*sRES %*sSHR S %*s%%CPU ",
            tf->pf_len.pid - 3, "", tf->pf_len.uid - 4, "", tf->pf_len.pr - 2,
            "", tf->pf_len.ni - 2, "", tf->pf_len.virt - 4, "",
            tf->pf_len.res - 3, "", tf->pf_len.shr - 3, "", tf->pf_len.cpu - 4,
            "");
    printw("%*s%%MEM %*sTIME+ COMMAND %*c", tf->pf_len.mem - 4, "",
            tf->pf_len.time - 5, "", tf->winsize->ws_col - (54 +
            (tf->pf_len.pid - 3 + tf->pf_len.uid - 4 + tf->pf_len.pr - 2 +
            tf->pf_len.ni - 2 + tf->pf_len.virt - 4 + tf->pf_len.res - 3 +
            tf->pf_len.shr - 3 + tf->pf_len.cpu - 4 + tf->pf_len.mem - 4 +
            tf->pf_len.time - 5)), ' ');
    attroff(COLOR_PAIR(BLACK_ON_WHITE));
}

static
void print_mem_header(tf_t *tf)
{
    printw("MiB Mem : %.1f total, %.1f free, %.1f used, %.1f buff/cache\n",
        tf->mem_infos.mem_total_mib, tf->mem_infos.mem_free_mib,
        tf->mem_infos.mem_used_mib, tf->mem_infos.buff_cache_mib);
    printw("MiB Swap: %.1f total, %.1f free, %.1f used. %.1f avail Mem",
        tf->mem_infos.swap_total_mib, tf->mem_infos.swap_free_mib,
        tf->mem_infos.swap_used_mib, tf->mem_infos.mem_available_mib);
}

static
void printer(tf_t *tf)
{
    get_load_avg(tf);
    get_uptime(tf);
    get_proc_list(tf);
    print_time();
    print_uptime(tf);
    printw(" %d user, load average: %.2f, %.2f, %.2f\n",
        tf->logged_in_users, tf->lavg.one_m, tf->lavg.five_m,
        tf->lavg.fifteen_m);
    printw("Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie\n",
        tf->processes.total, tf->processes.running, tf->processes.sleeping,
        tf->processes.stopped, tf->processes.zombie);
    printw("%%Cpu(s): %.1f us, %.1f sy, %.1f ni, %.1f id, %.1f wa, %.1f hi,",
        tf->cpuf_percentages[0], tf->cpuf_percentages[2],
        tf->cpuf_percentages[1], tf->cpuf_percentages[3],
        tf->cpuf_percentages[4], tf->cpuf_percentages[5]);
    printw(" %.1f si, %.1f st\n", tf->cpuf_percentages[6],
            tf->cpuf_percentages[7]);
    print_mem_header(tf);
    print_proc_header(tf);
}

static
void handle_ch(tf_t *tf, int ch)
{
    if (ch == KEY_DOWN && tf->min_displayed_i < tf->processes.total)
        tf->min_displayed_i++;
    if (ch == KEY_UP && tf->min_displayed_i > 0)
        tf->min_displayed_i--;
    if (ch == 'R')
        tf->reverse_sort = !tf->reverse_sort;
    if (ch == 'q')
        tf->opened = 0;
}

static
void init_loop(tf_t *tf)
{
    int ch;

    clear();
    tf->winsize->ws_col = COLS;
    tf->winsize->ws_row = LINES;
    get_memory_infos(tf);
    get_cpu_infos(&tf->cpuf_prev);
    get_logged_in_users(tf);
    printer(tf);
    print_procs(tf);
    ch = getch();
    if (ch)
        handle_ch(tf, ch);
    refresh();
    get_cpu_infos(&tf->cpuf_curr);
    calculate_cpu_usage(&tf->cpuf_prev, &tf->cpuf_curr,
        tf->cpuf_percentages);
    for (int i = 0; i < tf->processes.total; i++)
        free(tf->pf[i].cmd);
    free(tf->pf);
}

int init_ncurses(tf_t *tf)
{
    struct winsize winsize;
    int frames = 1;

    initscr();
    start_color();
    use_default_colors();
    curs_set(0);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
    keypad(stdscr, TRUE);
    timeout(tf->delay * 1000 ?: 3000);
    tf->winsize = &winsize;
    while (tf->opened && (!tf->frames || frames <= tf->frames))
        frames += (init_loop(tf), 1);
    delwin(stdscr);
    endwin();
    return TOP_SUCCESS;
}
