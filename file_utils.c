#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "file_utils.h"

int redirect_output(const char *filename, FILE **stream) {
    if (!filename || !stream) return 0;
    
    FILE *new_stream = freopen(filename, "w", *stream);
    if (!new_stream) {
        return 0;
    }
    
    return 1;
}

void restore_output(FILE *original_stream, FILE **current_stream) {
    if (original_stream && current_stream) {
        *current_stream = original_stream;
    }
}
