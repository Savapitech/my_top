/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const getters_t GETTERS[] = {
    { &get_name },
    { &get_pid },
    { NULL }
};

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
    while (fgets(line, 100, fp)) {
        for (int i = 0; GETTERS[i].ptr; i++)
            GETTERS[i].ptr(tf, i, line);
    }
    printw("%s %d", tf->pf[i].cmd, tf->pf[i].pid);
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

int get_proc_list(tf_t *tf)
{
    DIR *dir = opendir("/proc");
    struct dirent *sd;
    proc_info_t procf[get_proc_nbr()];
    int i = 0;

    if (dir == NULL)
        return TOP_FAILURE;
    if (!ARRAY_SIZE(procf))
        exit((fprintf(stderr, "top: Invalid proc number\n"), TOP_FAILURE));
    tf->pf = procf;
    tf->processes.total = ARRAY_SIZE(procf);
    for (sd = readdir(dir); sd != NULL; sd = readdir(dir)) {
        if (strisdigits(sd->d_name))
            fill_proc_info(tf, sd->d_name, i);
    }
    closedir(dir);
    return TOP_SUCCESS;
}
