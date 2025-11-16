#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "args_parser.h"

int parse_arguments(int argc, char *argv[], ProgramOptions *options) {
    int opt;
    struct option long_options[] = {
        {"users", no_argument, 0, 'u'},
        {"processes", no_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {"log", required_argument, 0, 'l'},
        {"errors", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };
    
    memset(options, 0, sizeof(ProgramOptions));
    
    while ((opt = getopt_long(argc, argv, "uphl:e:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'u':
                options->show_users = 1;
                break;
            case 'p':
                options->show_processes = 1;
                break;
            case 'h':
                options->show_help = 1;
                break;
            case 'l':
                options->log_file = strdup(optarg);
                break;
            case 'e':
                options->error_file = strdup(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-u|--users] [-p|--processes] [-h|--help] [-l|--log PATH] [-e|--errors PATH]\n", argv[0]);
                return 0;
        }
    }
    
    return 1;
}
