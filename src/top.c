/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <stdio.h>
#include <stdlib.h>

int top(int ac, char **av)
{
    tf_t tf = { .ac = ac, .av = av };

    init_ncurses(&tf);
    return TOP_SUCCESS;
}
