#ifndef PLAYER
#define PLAYER

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "animation.h"

typedef struct
{
    int x,y;
    int width, height;
} box_t;


typedef struct
{
    int wanted_animation;
    int animation_frame;
    int health;
    int current_animation;
    int animation_sprite_id;
    int x;

    bool is_neutral;
    bool is_blocking;

    ALLEGRO_BITMAP* sprite;

    box_t hurtbox;
    box_t hitbox;
} player;

bool is_neutral(enum animation a);

bool is_standing(player* p);


#endif