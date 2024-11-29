/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <stdio.h>
#include <unistd.h>

int get_load_avg(tf_t *tf)
{
    FILE *fp;

    fp = fopen("/proc/loadavg", "r");
    if (!fscanf(fp, "%f %f %f", &tf->lavg.one_m, &tf->lavg.five_m,
        &tf->lavg.fifteen_m))
        return (fclose(fp), TOP_FAILURE);
    fclose(fp);
    return TOP_SUCCESS;
}
