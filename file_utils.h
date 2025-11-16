#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

int redirect_output(const char *filename, FILE **stream);
void restore_output(FILE *original_stream, FILE **current_stream);

#endif
