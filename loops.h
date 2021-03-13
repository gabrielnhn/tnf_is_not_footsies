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
#include "sounds.h"
#include "score.h"

#define IS_CPU 1
#define IS_PLAYER2 2
#define QUIT 3
#define HELP 4

#define ROUND_START_TIMER 100 // amount of frames until round is declared over
#define ROUND_END_TIMER 200 // amount of frames until round is declared over

int main_menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE** sounds);

int level_menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE** sounds);

long match_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue,
                ALLEGRO_BITMAP*** animations, ALLEGRO_BITMAP* stage, 
                ALLEGRO_SAMPLE** sounds, int p2_option, int cpu_level);

void help_menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE** sounds);


#endif