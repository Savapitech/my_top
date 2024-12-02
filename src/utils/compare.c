/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "top.h"

int compare_pid(const void *first, const void *second)
{
    proc_info_t first_int = *(proc_info_t *)first;
    proc_info_t second_int = *(proc_info_t *)second;

    return second_int.pid - first_int.pid;
}

int compare_reverse_pid(const void *first, const void *second)
{
    proc_info_t first_int = *(proc_info_t *)first;
    proc_info_t second_int = *(proc_info_t *)second;

    return first_int.pid - second_int.pid;
}
