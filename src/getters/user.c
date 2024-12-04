/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

int get_logged_in_users(tf_t *tf)
{
    struct utmp entry;
    int fd;
    int user_count = 0;

    fd = open(_PATH_UTMP, O_RDONLY);
    if (fd == -1)
        return TOP_FAILURE;
    while (read(fd, &entry, sizeof(entry)) == sizeof(entry))
        if (entry.ut_type == USER_PROCESS)
            user_count++;
    close(fd);
    tf->logged_in_users = user_count;
    return TOP_SUCCESS;
}
