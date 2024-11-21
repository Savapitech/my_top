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

static
int fill_proc_info(tf_t *tf, char *pid, int i)
{
    int fd;
    char *file = malloc(strlen(pid) + 12);
    char buffer[10240];

    sprintf(file, "/proc/%s/stat", pid);
    fd = open(file, O_RDONLY);
    if (fd != -1) {
        read(fd, buffer, 10240);
        strtok(buffer, " ");
        tf->pf[i].pid = atof(pid);
        tf->pf[i].cmd = strdup(strtok(NULL, " ") + 1);
        tf->pf[i].cmd[strlen(tf->pf[i].cmd) - 1] = '\0';
        close(fd);
    }
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
    printw("pid %s\n", tf->pf[i].cmd);
    return TOP_SUCCESS;
}
