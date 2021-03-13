#include "player.h"

void init_players(player* p1, player* p2)
// initial players state
{
    p1->x = SCR_MIN + 90;
    p2->x = SCR_MAX - 90;
    
    p1->last_animation = idle;
    p2->last_animation = idle;
    
    p1->current_animation = idle;
    p2->current_animation = idle;

    p1->wanted_animation = idle;
    p2->wanted_animation = idle;

    
    p1->animation_frame = 0;
    p2->animation_frame = 0;

    p1->is_player1 = true;
    p2->is_player1 = false;

    p1->paused_frames = 0;
    p2->paused_frames = 0;

    p1->health = 100;
    p2->health = 100;

    p1->is_KOd = false;
    p2->is_KOd = false;

    update_boxes(p1, p2);

}

bool is_neutral(enum animation a)
// player can move freely
{
    switch (a)
    {
    case idle:
    case crouching:
    case walk_backwards:
    case walk_forward:
        return true;
    
    default:
        return false;
    }
}

bool is_blocking(enum animation a)
{
    switch (a)
    {
    case block_high:
    case block_low:
        return true;
    
    default:
        return false;
    }
}

bool is_hitstun(enum animation a)
{
    switch (a)
    {
    case high_hitstun:
    case low_hitstun:
        return true;
    
    default:
        return false;
    }
}

bool is_standing(player* p)
{
    switch (p->current_animation)
    {
    case crLP:
    case crMK:
    case block_low:
    case low_hitstun:
    case crouching:
    case fall:
    case rise:
        return false;
    
    default:
        return true;
    }
}

int middle_x(player p)
// compensating for sprite border
{
    return (p.x + 122);
}
