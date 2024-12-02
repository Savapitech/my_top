/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <dirent.h>
#include <fcntl.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    char *file = malloc(strlen(pid) + 13);
    char line[100];
    FILE *fp;

    sprintf(file, "/proc/%s/statm", pid);
    fp = fopen(file, "r");
    if (!fp)
        return TOP_FAILURE;
    if (!fgets(line, 100, fp))
        return TOP_FAILURE;
    for (int ii = 0; STATM_GETTERS[ii].ptr; ii++)
        STATM_GETTERS[ii].ptr(tf, i, line);
    if (file)
        free(file);
    fclose(fp);
    return TOP_SUCCESS;
}

static
int fill_with_stat(tf_t *tf, char *pid, int i)
{
    char *file = malloc(strlen(pid) + 12);
    char line[400];
    FILE *fp;

    sprintf(file, "/proc/%s/stat", pid);
    fp = fopen(file, "r");
    if (!fp)
        return TOP_FAILURE;
    if (!fgets(line, 400, fp))
        return TOP_FAILURE;
    for (int ii = 0; STAT_GETTERS[ii].ptr; ii++)
        STAT_GETTERS[ii].ptr(tf, i, line);
    if (file)
        free(file);
    fclose(fp);
    fill_with_statm(tf, pid, i);
    return TOP_SUCCESS;
}

static
int fill_proc_info(tf_t *tf, char *pid, int i)
{
    FILE *fp;
    char *file = malloc(strlen(pid) + 14);
    char line[100];

    sprintf(file, "/proc/%s/status", pid);
    fp = fopen(file, "r");
    if (!fp)
        return TOP_FAILURE;
    while (fgets(line, 100, fp))
        for (int ii = 0; STATUS_GETTERS[ii].ptr; ii++)
            STATUS_GETTERS[ii].ptr(tf, i, line);
    tf->pf_len.pid = (int)strlen(pid) > tf->pf_len.pid ?
        strlen(pid) : (size_t)tf->pf_len.pid;
    fill_with_stat(tf, pid, i);
    fclose(fp);
    if (file)
        free(file);
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
    if (!tf->reverse_sort)
        qsort(tf->pf, tf->processes.total, sizeof(proc_info_t), &compare_pid);
    else
        qsort(tf->pf, tf->processes.total, sizeof(proc_info_t),
            &compare_reverse_pid);
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
    tf->pf = malloc(sizeof(proc_info_t) * tf->processes.total);
    for (sd = readdir(dir); sd != NULL; sd = readdir(dir))
        if (strisdigits(sd->d_name))
            (fill_proc_info(tf, sd->d_name, i), i++);
    closedir(dir);
    return (sort_pf(tf), TOP_SUCCESS);
}
