#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdbool.h>
#include "animation.h"
#include "player.h"

typedef struct
{
    int start, end;
} range_t;

extern range_t active_frames[ANIMATIONS_N];
extern box_t hitboxes[ANIMATIONS_N];

void attacks_setup();

bool is_attack(enum animation a);

void update_boxes(player* p1, player* p2);

#endif