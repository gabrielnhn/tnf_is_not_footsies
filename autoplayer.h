#ifndef AUTOPLAYER_H
#define AUTOPLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

#define LEVELS_N 6 // amount of CPU levels
#define AUTOP_INTERVAL 40 // interval between moves

void autoplayer_setup();

void get_autoplayer_input(player* p1, player* p2, int cpu_level);

#endif