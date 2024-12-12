#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void get_command_line(char *pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/cmdline", pid);

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Failed to open cmdline file");
        return;
    }

    printf("Command line:\n");
    char cmdline[1024];
    fread(cmdline, sizeof(char), sizeof(cmdline), fp);
    printf("%s\n", cmdline);

    fclose(fp);
}

void get_process_time(char *pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/stat", pid);

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Failed to open stat file");
        return;
    }

    unsigned long utime, stime, cutime, cstime;
    int i;
    for (i = 0; i < 13; i++) fscanf(fp, "%*s"); // Skip to fields 14-17
    fscanf(fp, "%lu %lu %lu %lu", &utime, &stime, &cutime, &cstime);

    printf("Time spent by process:\n");
    printf(" - User mode: %lu ticks\n", utime);
    printf(" - Kernel mode: %lu ticks\n", stime);
    printf(" - User mode (children): %lu ticks\n", cutime);
    printf(" - Kernel mode (children): %lu ticks\n", cstime);

    fclose(fp);
}

void get_environment(char *pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/environ", pid);

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Failed to open environ file");
        return;
    }

    printf("Environment variables:\n");
    char env[4096];
    size_t nread = fread(env, sizeof(char), sizeof(env), fp);
    for (size_t i = 0; i < nread; i++) {
        if (env[i] == '\0') env[i] = '\n';
    }
    printf("%s\n", env);

    fclose(fp);
}

void get_memory_maps(char *pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/maps", pid);

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Failed to open maps file");
        return;
    }

    printf("Memory mappings (address space contents):\n");
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    char *pid = argv[1];

    printf("Process Information for PID %s\n\n", pid);
    get_command_line(pid);
    printf("\n");
    get_process_time(pid);
    printf("\n");
    get_environment(pid);
    printf("\n");
    get_memory_maps(pid);

    return 0;
}

