/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int read_file(tf_t *tf, char *path)
{
    FILE *fp;
    size_t len = 0;
    ssize_t read;
    size_t read_total = 0;
    int i = 0;

    fp = fopen(path, "r");
    if (fp == NULL)
        return TOP_FAILURE;
    for (read = getline(&tf->lines[i], &len, fp); read != -1;
        read = getline(&tf->lines[i], &len, fp)) {
        read_total += read;
        i++;
    }
    fclose(fp);
    return read_total;
}
