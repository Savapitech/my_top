/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"

int top(int ac, char **av)
{
    tf_t tf = { .ac = ac, .av = av };

    tf.pf_len = (proc_info_len_t){ 0 };
    init_ncurses(&tf);
    return TOP_SUCCESS;
}
