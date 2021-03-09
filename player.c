#include "player.h"

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

void update_hurtboxes(player* p1, player* p2)
// compensate for sprite border
// completely hardcoded
{
    p1->main_hurtbox.x = p1->x + 74 + 20;
    p1->main_hurtbox.width = 75 - 15;
    p1->main_hurtbox.y = PLAYER_HEIGHT + 62;
    p1->main_hurtbox.height = 96; 


    p2->main_hurtbox.x = p2->x + 74 + 20;
    p2->main_hurtbox.width = 75 - 15;
    p2->main_hurtbox.y = PLAYER_HEIGHT + 62;
    p2->main_hurtbox.height = 96; 
}

