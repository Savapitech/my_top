/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/


#ifndef TOP_H
    #define TOP_H
    #define DEBUG 0
    #define TOP_SUCCESS 0
    #define TOP_FAILURE 84
    #define BLACK_ON_WHITE 1
    #define ARRAY_SIZE(array) ((sizeof array) / (sizeof array[0]))
    #include <ncurses.h>
    #include <sys/ioctl.h>

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
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
} cpu_infos_t;

typedef struct {
    int pid;
    int uid;
    int gid;
    int pr;
    int ni;
    int virt;
    int res;
    int shr;
    int cpu;
    int mem;
    int time;
    int cmd;
} proc_info_len_t;

typedef struct {
    unsigned int pid;
    int uid;
    int gid;
    int pr;
    int ni;
    long long virt;
    long long res;
    long long shr;
    char state;
    int cpu;
    int mem;
    long long time;
    char *cmd;
} proc_info_t;

typedef struct getters_s getters_t;

typedef struct {
    int ac;
    char **av;
    flags_t flags;
    lavg_t lavg;
    double uptime;
    processes_t processes;
    proc_info_t *pf;
    proc_info_len_t pf_len;
    cpu_infos_t cpuf_prev;
    cpu_infos_t cpuf_curr;
    double cpuf_percentages[8];
    struct winsize *winsize;
} tf_t;

struct getters_s {
    int (*ptr)(tf_t *, int, char *);
};

//utils
int stridx(char const *, char);
int strisdigits(char *);
int floatlen(float, int);
int intlen(long long);

//core
int top(int, char **);
int parser(tf_t *);
void print_usage(void);
int get_load_avg(tf_t *);
int init_ncurses(tf_t *);
int get_uptime(tf_t *);
void print_uptime(tf_t *);
void print_time(void);
int get_proc_list(tf_t *);

// get
int get_name(tf_t *, int, char *);
int get_pid(tf_t *, int, char *);
int get_state(tf_t *, int, char *);
int get_uid(tf_t *, int, char *);
int get_gid(tf_t *, int, char *);
int get_virt(tf_t *, int, char *);
int get_res(tf_t *, int, char *);
int get_pr(tf_t *, int, char *);
int get_ni(tf_t *, int, char *);
int get_time(tf_t *, int, char *);
int get_cpu_infos(cpu_infos_t *);
int calculate_cpu_usage(cpu_infos_t *, cpu_infos_t *, double *);
#endif /* TOP_H */
