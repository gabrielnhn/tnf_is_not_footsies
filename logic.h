#include "player.h"
#include "display.h"

int check_hitboxes(player* p1, player* p2);

void init_players(player* p1, player* p2);

bool boxes_collide(box_t A, box_t B);

void choose_animation(player* p);