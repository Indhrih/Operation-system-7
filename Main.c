#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args_parser.h"
#include "users.h"
#include "processes.h"
#include "help.h"
#include "file_utils"

int main(int argc, char *argv[]) {
    ProgramOptions options = {0};
    
    // Парсинг аргументов командной строки
    if (!parse_arguments(argc, argv, &options)) {
        return 1;
    }
    
    // Обработка help
    if (options.show_help) {
        show_help();
        return 0;
    }
    
    // Настройка перенаправления вывода
    FILE *original_stdout = stdout;
    FILE *original_stderr = stderr;
    
    if (options.log_file) {
        if (!redirect_output(options.log_file, &stdout)) {
            fprintf(stderr, "Error: Cannot redirect output to %s\n", options.log_file);
            return 1;
        }
    }
    
    if (options.error_file) {
        if (!redirect_output(options.error_file, &stderr)) {
            fprintf(stderr, "Error: Cannot redirect errors to %s\n", options.error_file);
            return 1;
        }
    }
    
    // Выполнение запрошенных действий
    if (options.show_users) {
        show_users();
    }
    
    if (options.show_processes) {
        show_processes();
    }
    
    // Восстановление стандартных потоков
    if (options.log_file) {
        restore_output(original_stdout, &stdout);
    }
    
    if (options.error_file) {
        restore_output(original_stderr, &stderr);
    }
    
    return 0;
}
