#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <dirent.h> 
#include "utils.h"

// every possible animation
enum animation
{
    idle, walk_forward, walk_backwards, dash, backdash, crouching,
    crLP, crMK, dash_punch, overhead, block_high,block_low,fall, high_hitstun,
    low_hitstun, rise, geneijin
};
#define ANIMATIONS_N 17

#define INTERVAL 3 // interval of frames in which a sprite is used

int sprites_on_each_animation[ANIMATIONS_N];
int frames_on_each_animation[ANIMATIONS_N];

char* animation_enum_to_folder(enum animation a);

ALLEGRO_BITMAP*** load_sprites();

void destroy_sprites(ALLEGRO_BITMAP*** animations);

void animation_setup();

int sprite_for_frame(enum animation, int frame);



#endif