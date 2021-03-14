#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdbool.h>
#include "animation.h"
#include "player.h"
#include "logic.h"
#include "sounds.h"

typedef struct
{
    int start, end;
} range_t;

#define DEFAULT_STUN 6

#define WHIFF -1

extern range_t active_frames[ANIMATIONS_N];
extern box_t hitboxes[ANIMATIONS_N];
extern int blockstun[ANIMATIONS_N];
extern int hitstun[ANIMATIONS_N];
extern int damage[ANIMATIONS_N];

void attacks_setup();

bool is_attack(enum animation a);

box_t default_hurtbox_for_p(player* p);

void update_boxes(player* p1, player* p2);

int check_hitboxes(player* p1, player* p2);

#endif