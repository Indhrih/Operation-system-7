#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "processes.h"

typedef struct {
    int pid;
    char name[256];
} ProcessInfo;

int compare_processes(const void *a, const void *b) {
    const ProcessInfo *procA = (const ProcessInfo *)a;
    const ProcessInfo *procB = (const ProcessInfo *)b;
    return procA->pid - procB->pid;
}

int is_numeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

void show_processes(void) {
    DIR *dir;
    struct dirent *entry;
    ProcessInfo *processes = NULL;
    int count = 0;
    int capacity = 1000;
    
    processes = malloc(capacity * sizeof(ProcessInfo));
    if (!processes) {
        perror("malloc");
        return;
    }
    
    dir = opendir("/proc");
    if (!dir) {
        perror("opendir /proc");
        free(processes);
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (!is_numeric(entry->d_name)) continue;
        
        int pid = atoi(entry->d_name);
        if (pid == 0) continue;
        
        char path[512];
        snprintf(path, sizeof(path), "/proc/%d/comm", pid);
        
        FILE *file = fopen(path, "r");
        if (file) {
            if (count >= capacity) {
                capacity *= 2;
                ProcessInfo *temp = realloc(processes, capacity * sizeof(ProcessInfo));
                if (!temp) {
                    perror("realloc");
                    break;
                }
                processes = temp;
            }
            
            processes[count].pid = pid;
            if (fgets(processes[count].name, sizeof(processes[count].name), file)) {
                // Удаляем символ новой строки
                size_t len = strlen(processes[count].name);
                if (len > 0 && processes[count].name[len-1] == '\n') {
                    processes[count].name[len-1] = '\0';
                }
            } else {
                strcpy(processes[count].name, "unknown");
            }
            
            count++;
            fclose(file);
        }
    }
    
    closedir(dir);
    
    // Сортировка по PID
    qsort(processes, count, sizeof(ProcessInfo), compare_processes);
    
    // Вывод результатов
    printf("%-10s %s\n", "PID", "Process Name");
    printf("%-10s %s\n", "---", "------------");
    
    for (int i = 0; i < count; i++) {
        printf("%-10d %s\n", processes[i].pid, processes[i].name);
    }
    
    free(processes);
}
