#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include "animation.h"
#include "player.h"

#define KEY_SEEN 1
#define KEY_RELEASED 2

void input_setup();
int check_input(player* p1, player* p2,  ALLEGRO_EVENT event);