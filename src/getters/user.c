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
char *get_first_value(char const *line, char tok)
{
    size_t len = 0;
    char *result = NULL;

    for (; line[len]; len++)
        if (line[len] == tok)
            break;
    result = malloc((len + 1) * sizeof *result);
    memcpy(result, line, len);
    result[len] = '\0';
    return result;
}

static
char *get_value_tok(char const *line, int skip, char *tok)
{
    char *out;
    char const *s = line;
    size_t length;

    for (; skip >= 0; skip--) {
        s += strcspn(s, tok);
        s += strspn(s, tok);
    }
    length = strcspn(s, tok);
    out = malloc((length + 1) * sizeof *out);
    if (out == NULL)
        return NULL;
    memcpy(out, s, length);
    out[length] = '\0';
    return out;
}

static
char *parse_uid(char *line, int uid)
{
    char *user = get_first_value(line, ':');
    char *value_tok = get_value_tok(line, 1, ":");
    int passwd_uid = atoi(value_tok);

    if (passwd_uid == uid)
        return (free(value_tok), user);
    return (free(value_tok), NULL);
}

char *get_user_name(int uid)
{
    char file[] = "/etc/passwd";
    char line[400] = "";
    char *result = NULL;
    FILE *fp = NULL;

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
