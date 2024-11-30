/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include <stddef.h>
#include <utmp.h>

int get_logged_in_users(void)
{
    struct utmp *entry;
    int user_count = 0;

    setutent();
    for (entry = getutent(); entry != NULL; entry = getutent())
        if (entry->ut_type == USER_PROCESS)
            user_count++;
    endutent();
    return user_count;
}
