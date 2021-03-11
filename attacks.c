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

void update_boxes(player* p1, player* p2)
// compensate for sprite border
// completely hardcoded.
{
    p1->main_hurtbox.x = p1->x + 74 + 20;
    p1->main_hurtbox.width = 75 - 20;
    p1->main_hurtbox.y = PLAYER_HEIGHT + 62;
    p1->main_hurtbox.height = 96;

    if (is_attack(p1->current_animation) &&// move is an attack
        (inrange(p1->animation_frame,
        active_frames[p1->current_animation].start,
        active_frames[p1->current_animation].end))) // and it is during its active frames
    {
        p1->hitbox.x = (p1->main_hurtbox.x + p1->main_hurtbox.width) + hitboxes[p1->current_animation].x;
        p1->hitbox.width = /*p1->main_hurtbox.width + */ hitboxes[p1->current_animation].width;
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