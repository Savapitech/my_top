/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static
const char FLAGS[] = "Udnh";

static
void check_arg(void)
{
    if (stridx(FLAGS, optopt) >= 0)
        exit((fprintf(stderr, "top: -%c requires argument\n", optopt),
            TOP_FAILURE));
    else if (isprint(optopt)) {
        fprintf(stderr, "top: unknown option '%c'\n", optopt);
        exit((print_usage(), TOP_FAILURE));
    } else
        exit((fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt),
            TOP_FAILURE));
}

static
void switch_arg2(char c)
{
    switch (c) {
        case 'h':
            exit((print_usage(), TOP_SUCCESS));
            break;
        case '?':
        default:
            check_arg();
    }
}

static
void switch_arg(tf_t *tf, char c)
{
    switch (c) {
        case 'U':
            tf->user = optarg;
            break;
        case 'd':
            if (strisstr(optarg))
                exit((fprintf(stderr, "top: bad delay interval '%s'\n",
                    optarg), TOP_FAILURE));
            tf->delay = atof(optarg);
            break;
        case 'n':
            if (!strisdigits(optarg))
                exit((fprintf(stderr, "top: bad iterations argument '%s'\n",
                    optarg), TOP_FAILURE));
            tf->frames = atoi(optarg);
            break;
        default:
            switch_arg2(c);
    }
}

int parser(tf_t *tf)
{
    int c;

    opterr = 0;
    for (c = getopt(tf->ac, tf->av, "U:d:n:h"); c != -1;
        c = getopt(tf->ac, tf->av, "U:d:n:h"))
            switch_arg(tf, c);
    return TOP_SUCCESS;
}
