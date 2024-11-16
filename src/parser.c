/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static
const char FLAGS[] = "Udnh";

static
void parse_flags_value(tf_t *tf, int i)
{
    switch (*tf->av[i]) {
        case 'U':
            tf->av[i]++;
            if (!isalpha(*tf->av[i]))
                i++;
            if (i == tf->ac) {
                fprintf(stderr, "top: -U requires argument");
                exit(EXIT_FAILURE);
            }
            tf->flags.user = tf->av[i];
            break;
    }
}

static
void parse_flag(tf_t *tf, int i)
{
    tf->av[i]++;
    for (; *tf->av[i] != '\0'; tf->av[i]++) {
        if (stridx(FLAGS, *tf->av[i]) == -1) {
            fprintf(stderr, "top: unknown option '%c'\n", *tf->av[i]);
            printf_usage();
            exit(EXIT_FAILURE);
        }
        if (*tf->av[i] == 'h') {
            printf_usage();
            exit(EXIT_SUCCESS);
        }
        parse_flags_value(tf, i);
    }
}

static
int parse_arg(tf_t *tf, int i)
{
    for (; *tf->av[i] != '\0'; tf->av[i]++) {
        if (*tf->av[i] == '-')
            parse_flag(tf, i);
    }
    return EXIT_SUCCESS;
}

int parser(tf_t *tf)
{
    for (int i = 1; i < tf->ac; i++)
        if (parse_arg(tf, i))
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
