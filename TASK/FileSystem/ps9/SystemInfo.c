#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void get_cpu_info() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/cpuinfo");
        return;
    }

    int cpu_count = 0;
    char line[256];
    char *clock_speed = NULL;
    char *cores = NULL;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "processor", 9) == 0) {
            cpu_count++;
        } else if (strncmp(line, "cpu MHz", 7) == 0) {
            clock_speed = strdup(line + 11);
        } else if (strncmp(line, "cpu cores", 9) == 0) {
            cores = strdup(line + 11);
        }
    }

    printf("Number of CPUs: %d\n", cpu_count);
    if (clock_speed) printf("Clock speed: %s", clock_speed);
    if (cores) printf("Number of cores: %s", cores);

    free(clock_speed);
    free(cores);
    fclose(fp);
}

void get_kernel_version() {
    FILE *fp = fopen("/proc/version", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/version");
        return;
    }

    char version[256];
    fgets(version, sizeof(version), fp);
    printf("Linux Kernel Version: %s", version);

    fclose(fp);
}

void get_last_boot_time() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/uptime");
        return;
    }

    double uptime_seconds;
    fscanf(fp, "%lf", &uptime_seconds);
    time_t boot_time = time(NULL) - (time_t)uptime_seconds;

    struct tm *boot_tm = localtime(&boot_time);
    printf("System last booted at: %02d:%02d:%02d on %02d-%02d-%04d\n",
           boot_tm->tm_hour, boot_tm->tm_min, boot_tm->tm_sec,
           boot_tm->tm_mday, boot_tm->tm_mon + 1, boot_tm->tm_year + 1900);

    fclose(fp);
}

void get_load_average() {
    FILE *fp = fopen("/proc/loadavg", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/loadavg");
        return;
    }

    double loadavg_15;
    fscanf(fp, "%*f %*f %lf", &loadavg_15);
    printf("Average load (last 15 minutes): %.2f\n", loadavg_15);

    fclose(fp);
}

void get_memory_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/meminfo");
        return;
    }

    char label[256];
    unsigned long value;
    unsigned long mem_total = 0, mem_free = 0, swap_total = 0, swap_free = 0;

    while (fscanf(fp, "%s %lu kB", label, &value) == 2) {
        if (strcmp(label, "MemTotal:") == 0)
            mem_total = value;
        else if (strcmp(label, "MemFree:") == 0)
            mem_free = value;
        else if (strcmp(label, "SwapTotal:") == 0)
            swap_total = value;
        else if (strcmp(label, "SwapFree:") == 0)
            swap_free = value;
    }

    printf("Total usable memory: %lu kB\n", mem_total);
    printf("Currently free memory: %lu kB\n", mem_free);
    printf("Total swap space: %lu kB\n", swap_total);
    printf("Currently used swap space: %lu kB\n", swap_total - swap_free);

    fclose(fp);
}

void get_swap_partitions() {
    FILE *fp = fopen("/proc/swaps", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/swaps");
        return;
    }

    printf("Swap partitions:\n");
    char line[256];
    fgets(line, sizeof(line), fp); // skip header line

    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void get_cpu_time_spent() {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        return;
    }

    char cpu_label[16];
    unsigned long user_time, nice_time, system_time, idle_time;

    fscanf(fp, "%s %lu %lu %lu %lu", cpu_label, &user_time, &nice_time, &system_time, &idle_time);
    printf("CPU time spent in user mode: %lu ticks\n", user_time);
    printf("CPU time spent in kernel mode: %lu ticks\n", system_time);

    fclose(fp);
}

void get_context_switches() {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        return;
    }

    char label[64];
    unsigned long context_switches;

    while (fscanf(fp, "%s %lu", label, &context_switches) == 2) {
        if (strcmp(label, "ctxt") == 0) {
            printf("Number of context switches: %lu\n", context_switches);
            break;
        }
    }

    fclose(fp);
}

void get_interrupts() {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        return;
    }

    char label[64];
    unsigned long interrupts;

    while (fscanf(fp, "%s %lu", label, &interrupts) == 2) {
        if (strcmp(label, "intr") == 0) {
            printf("Number of interrupts handled: %lu\n", interrupts);
            break;
        }
    }

    fclose(fp);
}

int main() {
    printf("System Information:\n\n");
    get_cpu_info();
    printf("\n");
    get_kernel_version();
    printf("\n");
    get_last_boot_time();
    printf("\n");
    get_load_average();
    printf("\n");
    get_memory_info();
    printf("\n");
    get_swap_partitions();
    printf("\n");
    get_cpu_time_spent();
    printf("\n");
    get_context_switches();
    printf("\n");
    get_interrupts();
    return 0;
}

