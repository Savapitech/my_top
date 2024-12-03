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

    #define XCAT(val) #val
    #define CAT(val) XCAT(val)

    #define LONG_SIZE (sizeof CAT(LONG_MAX))

typedef struct {
    char *str;
    int count;
} buff_t;

typedef struct {
    char *user;
    float delay;
    uint32_t frames;
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
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;
    uint64_t steal;
} cpu_infos_t;

typedef struct {
    double mem_total_mib;
    double mem_free_mib;
    double mem_used_mib;
    double buff_cache_mib;
    double mem_available_mib;
    double swap_total_mib;
    double swap_free_mib;
    double swap_used_mib;
} mem_infos_t;

typedef struct {
    double sec;
    int int_sec;
    int min;
    int cent;
    uint64_t utime;
    uint64_t stime;
} top_time_t;

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
    double cpu;
    double mem;
    top_time_t time;
    char *cmd;
} proc_info_t;

typedef struct getters_s getters_t;

typedef struct {
    // main
    int ac;
    char **av;
    flags_t flags;
    bool reverse_sort;
    // win
    int opened;
    struct winsize *winsize;
    int min_displayed_i;
    // getters
    lavg_t lavg;
    double uptime;
    processes_t processes;
    proc_info_t *pf;
    proc_info_len_t pf_len;
    cpu_infos_t cpuf_prev;
    cpu_infos_t cpuf_curr;
    mem_infos_t mem_infos;
    double cpuf_percentages[8];
} tf_t;

struct getters_s {
    int (*ptr)(tf_t *, int, char *);
};

//utils
int stridx(char const *, char);
int strisdigits(char *);
int floatlen(float, int);
int intlen(long long);
int compare_pid(
    const proc_info_t *first,
    const proc_info_t *second,
    bool const *arg);
char const *get_value_tok(char *, int);

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
void get_memory_infos(tf_t *);
#endif /* TOP_H */
