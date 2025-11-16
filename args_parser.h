#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

typedef struct {
    int show_users;
    int show_processes;
    int show_help;
    char *log_file;
    char *error_file;
} ProgramOptions;

int parse_arguments(int argc, char *argv[], ProgramOptions *options);

#endif
