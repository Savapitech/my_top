/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"

int compare_pid(
    const proc_info_t *first,
    const proc_info_t *second,
    bool const *arg)
{
    int cmp = first->pid - second->pid;

    return (*(bool *)arg) ? - cmp : cmp;
}
