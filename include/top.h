/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/


#ifndef TOP_H
    #define TOP_H
    #define EXIT_SUCCESS 0
    #define EXIT_FAILURE 84

typedef struct {
    int ac;
    char **av;
} tf_t;

int top(int, char **);
#endif /* TOP_H */
