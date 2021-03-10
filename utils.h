#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void must_init(bool test, const char *description);

bool inrange(int x, int min, int max);

void bad_malloc();

bool in_array(char x, unsigned char* array, int array_size);

void print_array(unsigned char* array, int array_size);

#define STR_MAX 100

#endif
