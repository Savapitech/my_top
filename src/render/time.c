/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <ncurses.h>
#include <time.h>

void print_time(void)
{
    time_t tm = time(NULL);
    char *st = ctime(&tm);

    if (!st)
        return;
    st += 11;
    printw("top - %.8s", st);
}
