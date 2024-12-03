/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"

const tf_t BASE_TF_STATE = {
    .opened = 1
};

int top(int ac, char **av)
{
    tf_t tf = BASE_TF_STATE;

    tf.ac = ac;
    tf.av = av;
    tf.opened = 1;
    init_ncurses(&tf);
    return TOP_SUCCESS;
}
