/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <stdio.h>
#include <unistd.h>

int get_uptime(tf_t *tf)
{
    FILE *fp;

    fp = fopen("/proc/uptime", "r");
    fscanf(fp, "%lf", &tf->uptime);
    fclose(fp);
    return TOP_SUCCESS;
}