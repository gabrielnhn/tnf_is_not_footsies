#ifndef LOOPS_H
#define LOOPS_H

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "music.h"
#include "display.h"
#include "animation.h"
#include "utils.h"
#include "input.h"
#include "logic.h"
#include "autoplayer.h"

#define IS_CPU 1
#define IS_PLAYER2 2

#define FALL_ANIMATION_END 200 // amount of frames until round is declared over

int menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue);

void match_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue,
                ALLEGRO_BITMAP*** animations, ALLEGRO_BITMAP* stage, int option);

#endif