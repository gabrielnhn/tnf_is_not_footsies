#ifndef PLAYER
#define PLAYER

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct
{
    int x,y;
    int width, height;
} box_t;


typedef struct
{
    int animation_frame;
    // int health;
    int animation;
    int animation_sprite_id;
    int x;

    ALLEGRO_BITMAP* sprite;

    box_t hurtbox;
    box_t hitbox;
} player;

#endif