#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include "animation.h"
#include "player.h"
#include "utils.h"

#define KEY_SEEN 1
#define KEY_RELEASED 2

#define BUFFER_TIMER 9

enum input {UP, DOWN, LEFT, RIGHT, PUNCH, KICK};

unsigned char key[ALLEGRO_KEY_MAX];


void input_setup(player* p1, player* p2);
int check_input(player* p1, player* p2, ALLEGRO_EVENT event, long frame_count);

#endif