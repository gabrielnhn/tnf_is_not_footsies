#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include "animation.h"
#include "utils.h"

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
    int last_animation;
    int animation_sprite_id;
    int x;

    bool is_neutral;
    bool is_standing;
    bool is_blocking;

    ALLEGRO_BITMAP* sprite;

    box_t main_hurtbox;
    box_t hitbox;
} player;

#define SPEED 3 // character speed
#define PLAYER_HEIGHT 70

bool is_neutral(enum animation a);

bool is_standing(player* p);

int middle_x(player p);

void update_hurtboxes(player* p1, player* p2);

#endif