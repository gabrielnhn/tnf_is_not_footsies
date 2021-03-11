#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdbool.h>
#include "animation.h"
#include "player.h"
#include "logic.h"

typedef struct
{
    int start, end;
} range_t;

#define DEFAULT_STUN 6

extern range_t active_frames[ANIMATIONS_N];
extern box_t hitboxes[ANIMATIONS_N];
extern int on_block_advantage[ANIMATIONS_N];
extern int on_hit_advantage[ANIMATIONS_N];

void attacks_setup();

bool is_attack(enum animation a);

void update_boxes(player* p1, player* p2);

int check_hitboxes(player* p1, player* p2);

#endif