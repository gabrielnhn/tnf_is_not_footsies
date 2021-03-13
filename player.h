#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct
{
    int x,y;
    int width, height;
} box_t;

typedef struct
{
    // input related:
    unsigned char input_buffer[30];
    int buffer_length;
    long last_input_frame;

    // sprite/animation related
    int last_animation;
    int current_animation;
    int wanted_animation;
    int animation_sprite_id;
    int animation_frame;
    ALLEGRO_BITMAP* sprite;
    int paused_frames;

    // game state related
    int health;
    int x;
    bool is_player1;
    bool is_neutral;
    bool is_standing;
    bool is_inputting_block;
    bool is_KOd;
    int rounds_won;

    box_t main_hurtbox;
    box_t move_hurtbox;
    box_t hitbox;
    bool hitbox_is_active;

} player;

#include "animation.h"
#include "utils.h"
#include "display.h"
#include "logic.h"

#define SPEED 3 // character speed
#define PLAYER_HEIGHT 70

void init_players(player* p1, player* p2);

bool is_blocking(enum animation a);

bool is_hitstun(enum animation a);

bool is_neutral(enum animation a);

bool is_standing(player* p);

int middle_x(player p);

#endif