/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** _
*/

#include "top.h"
#include <string.h>

int get_cpu_infos(cpu_infos_t *cpuf)
{
    FILE *file = fopen("/proc/stat", "r");
    char buffer[256];

    if (!file)
        return (perror("fopen"), -1);
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("fgets");
        return (fclose(file), TOP_FAILURE);
    }
    fclose(file);
    sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu %lu",
        &cpuf->user, &cpuf->nice, &cpuf->system, &cpuf->idle,
        &cpuf->iowait, &cpuf->irq, &cpuf->softirq, &cpuf->steal);
    return TOP_SUCCESS;
}

int calculate_cpu_usage(cpu_infos_t *prev, cpu_infos_t *curr,
    double *percentages)
{
    uint64_t prev_total = prev->user + prev->nice + prev->system +
        prev->idle + prev->iowait + prev->irq + prev->softirq + prev->steal;
    uint64_t curr_total = curr->user + curr->nice + curr->system +
        curr->idle + curr->iowait + curr->irq + curr->softirq + curr->steal;
    uint64_t tot_dif = curr_total - prev_total;
    uint64_t *prev_ptr = (uint64_t *)&prev->user;
    uint64_t *curr_ptr = (uint64_t *)&curr->user;
    size_t perc_size = sizeof((tf_t *)0)->cpuf_percentages / sizeof(double);

    if (tot_dif == 0)
        return (memset(percentages, 0, perc_size * sizeof(double)),
            TOP_SUCCESS);
    for (uint64_t i = 0; i < perc_size; i++)
        percentages[i] = 100.0 * (double)(curr_ptr[i] - prev_ptr[i]) / tot_dif;
    return TOP_SUCCESS;
}

static
uint64_t get_meminfo_value(const char *key)
{
    FILE *file = fopen("/proc/meminfo", "r");
    char buffer[256];
    uint64_t value = 0;

    if (!file)
        return (perror("fopen"),
            TOP_FAILURE);
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, key, strlen(key)) == 0) {
            sscanf(buffer + strlen(key), " %lu kB", &value);
            break;
        }
    }
    fclose(file);
    return value;
}

void get_memory_infos(tf_t *tf)
{
    uint64_t mem_total = get_meminfo_value("MemTotal:");
    uint64_t mem_free = get_meminfo_value("MemFree:");
    uint64_t buffers = get_meminfo_value("Buffers:");
    uint64_t shrec = get_meminfo_value("SReclaimable:");
    uint64_t cached = shrec + get_meminfo_value("Cached:");
    uint64_t mem_available = get_meminfo_value("MemAvailable:");
    uint64_t swap_total = get_meminfo_value("SwapTotal:");
    uint64_t swap_free = get_meminfo_value("SwapFree:");
    uint64_t mem_used = mem_total - mem_available;
    uint64_t buff_cache = buffers + cached;
    uint64_t swap_used = swap_total - swap_free;

    tf->mem_infos.mem_total_mib = mem_total / 1024.0;
    tf->mem_infos.mem_free_mib = mem_free / 1024.0;
    tf->mem_infos.mem_used_mib = mem_used / 1024.0;
    tf->mem_infos.buff_cache_mib = buff_cache / 1024.0;
    tf->mem_infos.mem_available_mib = mem_available / 1024.0;
    tf->mem_infos.swap_total_mib = swap_total / 1024.0;
    tf->mem_infos.swap_free_mib = swap_free / 1024.0;
    tf->mem_infos.swap_used_mib = swap_used / 1024.0;
}
