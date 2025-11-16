#include <stdio.h>
#include "help.h"

void show_help(void) {
    printf("System Information Tool\n");
    printf("Usage: system_info_tool [OPTIONS]\n\n");
    printf("Options:\n");
    printf("  -u, --users        Display users and their home directories (sorted alphabetically)\n");
    printf("  -p, --processes    Display running processes (sorted by PID)\n");
    printf("  -h, --help         Show this help message and exit\n");
    printf("  -l, --log PATH     Redirect output to specified file\n");
    printf("  -e, --errors PATH  Redirect error output to specified file\n\n");
    printf("Examples:\n");
    printf("  system_info_tool -u --log /tmp/users.txt\n");
    printf("  system_info_tool -p -e /tmp/errors.log\n");
    printf("  system_info_tool -u -p --log /tmp/system_info.txt\n");
}
