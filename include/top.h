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
    #define ARRAY_SIZE(array) ((sizeof array) / (sizeof array[0]))

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
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
} processes_t;

typedef struct {
    float pid;
    int uid;
    int pr;
    int ni;
    float virt;
    float res;
    float shr;
    int s;
    int cpu;
    int mem;
    int time;
    char *cmd;

} proc_info_t;

typedef struct {
    int ac;
    char **av;
    flags_t flags;
    lavg_t lavg;
    double uptime;
    processes_t processes;
    proc_info_t *pf;
    char *lines[20];
} tf_t;

//utils
int stridx(char const *, char);
int strisdigits(char *);

//core
int top(int, char **);
int parser(tf_t *);
void print_usage(void);
int get_load_avg(tf_t *);
int read_file(tf_t *, char *);
int init_ncurses(tf_t *);
int get_uptime(tf_t *);
void print_uptime(tf_t *);
void print_time(void);
int get_proc_list(tf_t *);
#endif /* TOP_H */
