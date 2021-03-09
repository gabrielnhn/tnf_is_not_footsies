#ifndef DISPLAY
#define DISPLAY

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"

#define WIDTH 400
#define HEIGHT 260

#define SCALE 3



ALLEGRO_DISPLAY *create_display();
void destroy_display(ALLEGRO_DISPLAY *disp);
void draw_display(ALLEGRO_BITMAP *stage, player *player1, player *player2);

#endif