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
    char *user;
    float delay;
    int frames;
} flags_t;

typedef struct {
    int ac;
    char **av;
    flags_t flags;
} tf_t;

//utils
int stridx(char const *, char);

//core
int top(int, char **);
int parser(tf_t *);
void printf_usage(void);
#endif /* TOP_H */
