#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "player.h"

#define WIDTH 400
#define HEIGHT 260
#define SCALE 3

// I don't know why, but these are the values in the X axis
// that define the range the players can be: 
#define SCR_MIN -95
#define SCR_MAX 245

#define MENU_RECT_BORDER 10

ALLEGRO_DISPLAY *create_display();
void destroy_display(ALLEGRO_DISPLAY *disp);

void draw_boxes();
void draw_match(ALLEGRO_BITMAP *stage, player *player1, player *player2);
void draw_menu(int option);

#endif