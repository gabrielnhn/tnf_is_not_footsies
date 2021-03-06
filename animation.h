#ifndef ANIMATION
#define ANIMATION

#include <stdio.h>
#include <stdlib.h>

// every possible animation
enum animation
{
    idle, walk_forward, walk_backwards, dash, backdash, crouching,
    crLP, crMK, dash_punch, overhead, block_high,block_low,fall, high_hitstun,
    low_hitstun, rise
};

char* animation_enum_to_folder(enum animation a);

#endif