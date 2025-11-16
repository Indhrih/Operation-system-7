#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include "users.h"

typedef struct {
    char *username;
    char *home_dir;
} UserInfo;

int compare_users(const void *a, const void *b) {
    const UserInfo *userA = (const UserInfo *)a;
    const UserInfo *userB = (const UserInfo *)b;
    return strcmp(userA->username, userB->username);
}

void show_users(void) {
    struct passwd *pwd;
    UserInfo *users = NULL;
    int count = 0;
    int capacity = 100;
    
    users = malloc(capacity * sizeof(UserInfo));
    if (!users) {
        perror("malloc");
        return;
    }
    
    setpwent();
    
    while ((pwd = getpwent()) != NULL) {
        if (count >= capacity) {
            capacity *= 2;
            UserInfo *temp = realloc(users, capacity * sizeof(UserInfo));
            if (!temp) {
                perror("realloc");
                free(users);
                endpwent();
                return;
            }
            users = temp;
        }
        
        users[count].username = strdup(pwd->pw_name);
        users[count].home_dir = strdup(pwd->pw_dir);
        count++;
    }
    
    endpwent();
    
    // Сортировка по алфавиту
    qsort(users, count, sizeof(UserInfo), compare_users);
    
    // Вывод результатов
    printf("%-20s %s\n", "Username", "Home Directory");
    printf("%-20s %s\n", "--------", "--------------");
    
    for (int i = 0; i < count; i++) {
        printf("%-20s %s\n", users[i].username, users[i].home_dir);
        free(users[i].username);
        free(users[i].home_dir);
    }
    
    free(users);
}
