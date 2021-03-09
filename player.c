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