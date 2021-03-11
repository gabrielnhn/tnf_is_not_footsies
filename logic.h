#ifndef LOGIC_H
#define LOGIC_H

#include "player.h"
#include "display.h"
#include "attacks.h"

void init_players(player* p1, player* p2);

bool boxes_collide(box_t A, box_t B);

void choose_animation(player* p);

int speed_for_animation(enum animation a);

void check_movement(player* p1, player* p2);

#endif
