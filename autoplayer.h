#ifndef AUTOPLAYER_H
#define AUTOPLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

#define LEVELS_N 6

void autoplayer_setup();

void get_autoplayer_input(player* p1, player* p2, int cpu_level);

#endif