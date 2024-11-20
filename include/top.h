/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/


#ifndef TOP_H
    #define TOP_H
    #define TOP_SUCCESS 0
    #define TOP_FAILURE 84

typedef struct {
    char *str;
    int count;
} buff_t;

typedef struct {
    char *user;
    float delay;
    int frames;
} flags_t;

typedef struct {
    float one_m;
    float five_m;
    float fifteen_m;
} lavg_t;

typedef struct {
    int ac;
    char **av;
    flags_t flags;
    lavg_t lavg;
    double uptime;
    char *lines[20];
} tf_t;

//utils
int stridx(char const *, char);

//core
int top(int, char **);
int parser(tf_t *);
void print_usage(void);
int get_load_avg(tf_t *);
int read_file(tf_t *, char *);
int init_ncurses(tf_t *);
int get_uptime(tf_t *);
void print_uptime(tf_t *);
#endif /* TOP_H */
