/*
** EPITECH PROJECT, 2024
** __
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
    sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
        &cpuf->user, &cpuf->nice, &cpuf->system, &cpuf->idle,
        &cpuf->iowait, &cpuf->irq, &cpuf->softirq, &cpuf->steal);
    return TOP_SUCCESS;
}

int calculate_cpu_usage(cpu_infos_t *prev, cpu_infos_t *curr,
    double *percentages)
{
    unsigned long long prev_total = prev->user + prev->nice + prev->system +
        prev->idle + prev->iowait + prev->irq + prev->softirq + prev->steal;
    unsigned long long curr_total = curr->user + curr->nice + curr->system +
        curr->idle + curr->iowait + curr->irq + curr->softirq + curr->steal;
    unsigned long long tot_dif = curr_total - prev_total;

    if (tot_dif == 0)
        return (memset(percentages, 0, 8 * sizeof(double)), TOP_SUCCESS);
    percentages[0] = 100.0 * (double)(curr->user - prev->user) / tot_dif;
    percentages[1] = 100.0 * (double)(curr->nice - prev->nice) / tot_dif;
    percentages[2] = 100.0 * (double)(curr->system - prev->system) / tot_dif;
    percentages[3] = 100.0 * (double)(curr->idle - prev->idle) / tot_dif;
    percentages[4] = 100.0 * (double)(curr->iowait - prev->iowait) / tot_dif;
    percentages[5] = 100.0 * (double)(curr->irq - prev->irq) / tot_dif;
    percentages[6] = 100.0 * (double)(curr->softirq - prev->softirq) / tot_dif;
    percentages[7] = 100.0 * (double)(curr->steal - prev->steal) / tot_dif;
    return TOP_SUCCESS;
}
