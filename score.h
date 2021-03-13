#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "autoplayer.h"

#define EXTRA_MEMORY 150

void check_for_highscore(int level, int frames);
void get_highscores(int* array);

#endif