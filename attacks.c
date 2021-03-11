#include "attacks.h"


range_t active_frames[ANIMATIONS_N];
box_t hitboxes[ANIMATIONS_N];

void attacks_setup()
{
    for(int i = 0; i < ANIMATIONS_N; i++)
    {
        switch (i)
        {
        case crLP:
            active_frames[i] = (range_t){3 * INTERVAL, 5 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 50, 0};
            break;

        case crMK:
            active_frames[i] = (range_t){4 * INTERVAL, 6 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 85, 0};
            break;

        case dash_punch:
            active_frames[i] = (range_t){7 * INTERVAL, 9 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 60, 0};
            break;
        
        case overhead:
            active_frames[i] = (range_t){9 * INTERVAL, 11 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 50, 0};
            break;
        
        default:
            active_frames[i] = (range_t){-1, -1}; // no active frames, not an attack
            break;
        }
    }
}

bool is_attack(enum animation a)
{
    switch (a)
    {
    case crLP:
    case crMK:
    case dash_punch:
    case overhead:
        return true;
    
    default:
        return false;
    }
}

bool has_hurtbox(enum animation a)
{
    switch (a)
    {
    case low_hitstun:
    case high_hitstun:
    case block_low:
    case block_high:
        return false;
    
    default:
        return true;
    }
}

void update_boxes(player* p1, player* p2)
// compensate for sprite border
// completely hardcoded.
{
    if (has_hurtbox(p1->current_animation))
    {
        p1->main_hurtbox.x = p1->x + 74 + 20;
        p1->main_hurtbox.width = 75 - 20;
        p1->main_hurtbox.y = PLAYER_HEIGHT + 62;
        p1->main_hurtbox.height = 96;
    }
    else
    {
        p1->main_hurtbox.x = 0;
        p1->main_hurtbox.width = 0;
        p1->main_hurtbox.y = 0;
        p1->main_hurtbox.height = 0;
    }

    if (is_attack(p1->current_animation) &&// move is an attack
        (inrange(p1->animation_frame,
        active_frames[p1->current_animation].start,
        active_frames[p1->current_animation].end))) // and it is during its active frames
    {
        p1->hitbox.x = (p1->main_hurtbox.x + p1->main_hurtbox.width) + hitboxes[p1->current_animation].x;
        p1->hitbox.width = hitboxes[p1->current_animation].width;
        p1->hitbox.y = p1->main_hurtbox.y;
        p1->hitbox.height = p1->main_hurtbox.height;
    }
    else // no hitbox
    {
        p1->hitbox.x = 0;
        p1->hitbox.width = 0;
        p1->hitbox.y = 0;
        p1->hitbox.height = 0;
    }
    if (is_attack(p1->current_animation))
    {
        p1->move_hurtbox.x = (p1->main_hurtbox.x + p1->main_hurtbox.width) + hitboxes[p1->current_animation].x;
        p1->move_hurtbox.width = /*p1->main_hurtbox.width + */ hitboxes[p1->current_animation].width - 5;
        p1->move_hurtbox.y = p1->main_hurtbox.y;
        p1->move_hurtbox.height = p1->main_hurtbox.height;
    }
    else
    {
        p1->move_hurtbox.x = 0;
        p1->move_hurtbox.width = 0;
        p1->move_hurtbox.y = 0;
        p1->move_hurtbox.height = 0;
    }

    p2->main_hurtbox.x = p2->x + 74 + 20;
    p2->main_hurtbox.width = 75 - 15;
    p2->main_hurtbox.y = PLAYER_HEIGHT + 62;
    p2->main_hurtbox.height = 96; 
}

int check_hitboxes(player* p1, player* p2)
{
    bool p1_was_hit = false;
    bool p1_blocked = false;
    bool p2_was_hit = false;
    bool p2_blocked = false;

    if (boxes_collide(p1->hitbox, p2->main_hurtbox) ||
        boxes_collide(p1->hitbox, p2->move_hurtbox))
        p2_was_hit = true;

    if (boxes_collide(p2->hitbox, p1->main_hurtbox) ||
        boxes_collide(p2->hitbox, p1->move_hurtbox))
        p1_was_hit = true;
    
    // set flags
    if (p1_was_hit)
    {
        if (p1->is_blocking)
        {
            p1_blocked = true;

            if (p2->current_animation == crMK) // low attack
            {
                if (p1->is_standing)
                    p1_blocked = false;
            }
            else if (p2->current_animation == overhead) // high attack
            {
                if (!p1->is_standing)
                    p1_blocked = false;
            } 
        }
        else
        {
            p1_blocked = false;
        }
    }

    if (p2_was_hit)
    {
        if (p2->is_blocking)
        {
            p2_blocked = true;

            if (p1->current_animation == crMK) // low attack
            {
                if (p2->is_standing)
                    p2_blocked = false;
            }
            else if (p1->current_animation == overhead) // high attack
            {
                if (!p2->is_standing)
                    p2_blocked = false;
            } 
        }
        else
        {
            p2_blocked = false;
        }
    }

    // handle flags
    if(p1_was_hit)
    {
        if (!p1_blocked)
        {
            if (p1->is_standing)
            {
                p1->wanted_animation = high_hitstun;
                p1->animation_frame = 0;
            }
            else
            {
                p1->wanted_animation = low_hitstun;
                p1->animation_frame = 0;
            }
        }
        else
        {
            if (p1->is_standing)
            {
                p1->wanted_animation = block_high;
                p1->animation_frame = 0;
            }
            else
            {
                p1->wanted_animation = block_low;
                p1->animation_frame = 0;
            }
        }
    }

    if(p2_was_hit)
    {
        if (!p2_blocked)
        {
            if (p2->is_standing)
            {
                p2->wanted_animation = high_hitstun;
                p2->animation_frame = 0;
            }
            else
            {
                p2->wanted_animation = low_hitstun;
                p2->animation_frame = 0;
            }
        }
        else
        {
            if (p2->is_standing)
            {
                p2->wanted_animation = block_high;
                p2->animation_frame = 0;
            }
            else
            {
                p2->wanted_animation = block_low;
                p2->animation_frame = 0;
            }
        }
    }

    return (p1_was_hit || p2_was_hit);
}