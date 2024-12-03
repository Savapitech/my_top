/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#define _GNU_SOURCE

#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "top.h"

const getters_t STATUS_GETTERS[] = {
    { &get_name },
    { &get_pid },
    { &get_state },
    { &get_uid },
    { &get_gid },
    { NULL }
};

const getters_t STAT_GETTERS[] = {
    { &get_pr },
    { &get_ni },
    { &get_time },
    { NULL }
};

const getters_t STATM_GETTERS[] = {
    { &get_res },
    { &get_virt },
    { NULL }
};

static
int fill_with_statm(tf_t *tf, char *pid, int i)
{
    char file[sizeof("/proc//statm") + LONG_SIZE];
    char line[100];
    FILE *fp;

    if (strlen(pid) > LONG_SIZE)
        return TOP_FAILURE;
    snprintf(file, sizeof file, "/proc/%s/statm", pid);
    fp = fopen(file, "r");
    if (!fp)
        return TOP_FAILURE;
    if (!fgets(line, 100, fp))
        return TOP_FAILURE;
    for (int ii = 0; STATM_GETTERS[ii].ptr != NULL; ii++)
        STATM_GETTERS[ii].ptr(tf, i, line);
    fclose(fp);
    return TOP_SUCCESS;
}

static
int fill_with_stat(tf_t *tf, char *pid, int i)
{
    char file[sizeof("/proc//stat") + LONG_SIZE];
    char line[400];
    FILE *fp;

    if (strlen(pid) > LONG_SIZE)
        return TOP_FAILURE;
    snprintf(file, sizeof file, "/proc/%s/stat", pid);
    fp = fopen(file, "r");
    if (!fp)
        return TOP_FAILURE;
    if (!fgets(line, 400, fp))
        return TOP_FAILURE;
    for (int ii = 0; STAT_GETTERS[ii].ptr != NULL; ii++)
        STAT_GETTERS[ii].ptr(tf, i, line);
    fclose(fp);
    fill_with_statm(tf, pid, i);
    return TOP_SUCCESS;
}

static
int fill_proc_info(tf_t *tf, char *pid, int i)
{
    FILE *fp;
    char file[sizeof("/proc//status") + LONG_SIZE];
    char line[100];

    if (strlen(pid) > LONG_SIZE)
        return TOP_FAILURE;
    snprintf(file, sizeof file, "/proc/%s/status", pid);
    fp = fopen(file, "r");
    if (!fp)
        return TOP_FAILURE;
    while (fgets(line, 100, fp))
        for (int ii = 0; STATUS_GETTERS[ii].ptr != NULL; ii++)
            STATUS_GETTERS[ii].ptr(tf, i, line);
    tf->pf_len.pid = (int)strlen(pid) > tf->pf_len.pid ?
        strlen(pid) : (size_t)tf->pf_len.pid;
    fill_with_stat(tf, pid, i);
    fclose(fp);
    return TOP_SUCCESS;
}

static
int get_proc_nbr(void)
{
    DIR *dir = opendir("/proc");
    struct dirent *sd;
    int count = 0;

    if (dir == NULL)
        return 0;
    for (sd = readdir(dir); sd != NULL; sd = readdir(dir))
        if (strisdigits(sd->d_name))
            count++;
    closedir(dir);
    return count;
}

static
void sort_pf(tf_t *tf)
{
    qsort_r(tf->pf, tf->processes.total, sizeof *tf->pf,
        (__compar_d_fn_t)compare_pid, &tf->reverse_sort);
}

int get_proc_list(tf_t *tf)
{
    DIR *dir = opendir("/proc");
    struct dirent *sd;
    int i = 0;

    if (dir == NULL)
        return TOP_FAILURE;
    tf->processes = (processes_t){ 0 };
    tf->processes.total = get_proc_nbr();
    if (!tf->processes.total)
        exit((fprintf(stderr, "top: Invalid proc number\n"), TOP_FAILURE));
    tf->pf = calloc(tf->processes.total, sizeof *tf->pf);
    if (tf->pf == NULL)
        return -1;
    for (sd = readdir(dir); sd != NULL; sd = readdir(dir))
        if (strisdigits(sd->d_name))
            fill_proc_info(tf, sd->d_name, i), i++;
    closedir(dir);
    return (sort_pf(tf), TOP_SUCCESS);
}
