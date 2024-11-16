/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <stdio.h>

int top(int ac, char **av)
{
    tf_t tf = { .ac = ac, .av = av };

    if (parser(&tf))
        return (EXIT_FAILURE);
    printf("User: %s, Delay: %f, Frames: %d\n", tf.flags.user, tf.flags.delay,
        tf.flags.frames);
    return EXIT_SUCCESS;
}
