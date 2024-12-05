/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utmp.h>

static
char *parse_uid(char *line, int uid)
{
    char *user = strtok(line, ":");

    strtok(NULL, ":");
    if (atoi(strtok(NULL, ":")) == uid)
        return user;
    return NULL;
}

char *get_user_name(int uid)
{
    char file[] = "/etc/passwd";
    char line[400];
    char *result;
    FILE *fp;

    fp = fopen(file, "r");
    if (!fp)
        return NULL;
    while (fgets(line, 400, fp)) {
        result = parse_uid(line, uid);
        if (result)
            break;
    }
    fclose(fp);
    return result;
}

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
