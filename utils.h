#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void must_init(bool test, const char *description);

bool inrange(int x, int min, int max);

void bad_malloc();

#define STR_MAX 100
#define SPEED 3 // character speed
#define PLAYER_HEIGHT 70