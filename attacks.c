#include "attacks.h"


// Proprieties of each attack
range_t active_frames[ANIMATIONS_N];
box_t hitboxes[ANIMATIONS_N];
int blockstun[ANIMATIONS_N];
int hitstun[ANIMATIONS_N];
int damage[ANIMATIONS_N];

void attacks_setup()
// set the values for each attack
{
    for(int i = 0; i < ANIMATIONS_N; i++)
    {
        switch (i)
        {
        case crLP:
            active_frames[i] = (range_t){3 * INTERVAL, 5 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 50, 0};
            blockstun[i] = +3;
            hitstun[i] = +3;
            damage[i] = 15;
            break;

        case crMK:
            active_frames[i] = (range_t){4 * INTERVAL, 6 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 85, 0};
            blockstun[i] = -1;
            hitstun[i] = +5; // 13
            damage[i] = 20;
            break;

        case dash_punch:
            // active_frames[i] = (range_t){7 * INTERVAL, 9 * INTERVAL};
            active_frames[i] = (range_t){2 * INTERVAL, 9 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 60, 0};
            blockstun[i] = -16;
            hitstun[i] = 14;
            damage[i] = 50;
            break;
        
        case overhead:
            active_frames[i] = (range_t){9 * INTERVAL, 11 * INTERVAL};
            hitboxes[i] = (box_t){0, 0, 50, 0};
            blockstun[i] = -8;
            hitstun[i] = -3;
            damage[i] = 25;
            break;
        
        default:
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
// return true only if "animation a" has a hurtbox
{
    switch (a)
    {
    case geneijin:
    case fall:
        return false;
    
    default:
        return true;
    }
}

box_t default_hurtbox_for_p(player* p)
// return the hardcoded main hurtbox of each player
{
    box_t default_box;
    if (p->is_player1)
    {
        default_box.x = p->x + 74 + 20;
        default_box.width = 75 - 20;
        default_box.y = PLAYER_HEIGHT + 62;
        default_box.height = 96;
    }
    else
    {
        default_box.x = p->x + 74 + 20;
        default_box.width = 75 - 15;
        default_box.y = PLAYER_HEIGHT + 62;
        default_box.height = 96;
    }
    return default_box;
}

void update_boxes(player* p1, player* p2)
// update main hurtbox, move hurtbox and hitbox of each player 
{
    if (has_hurtbox(p1->current_animation))
    {
        p1->main_hurtbox = default_hurtbox_for_p(p1);
    }
    else
    {
        p1->main_hurtbox.x = 0;
        p1->main_hurtbox.width = -1;
        p1->main_hurtbox.y = 0;
        p1->main_hurtbox.height = 0;
    }

    if (is_attack(p1->current_animation) &&// move is an attack
        (inrange(p1->animation_frame,
        active_frames[p1->current_animation].start,
        active_frames[p1->current_animation].end))) // and it is during its active frames
    {
        if (p1->animation_frame == active_frames[p1->current_animation].start)
        {
            // activate it on the first frame of the animation
            if(p1->paused_frames == 0)
                p1->hitbox_is_active = true;    
        }
            
        p1->hitbox.x = (p1->main_hurtbox.x + p1->main_hurtbox.width) + hitboxes[p1->current_animation].x;
        p1->hitbox.width = hitboxes[p1->current_animation].width;
        p1->hitbox.y = p1->main_hurtbox.y;
        p1->hitbox.height = p1->main_hurtbox.height;
    }
    else // no hitbox
    {
        p1->hitbox.x = 0;
        p1->hitbox.width = -1;
        p1->hitbox.y = 0;
        p1->hitbox.height = 0;
        p1->hitbox_is_active = false;
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
        p1->move_hurtbox.width = -1;
        p1->move_hurtbox.y = 0;
        p1->move_hurtbox.height = 0;
    }

    if (has_hurtbox(p2->current_animation))
    {
        p2->main_hurtbox = default_hurtbox_for_p(p2);
    }
    else
    {
        p2->main_hurtbox.x = 0;
        p2->main_hurtbox.width = -1;
        p2->main_hurtbox.y = 0;
        p2->main_hurtbox.height = 0;
    }
    if (is_attack(p2->current_animation) &&// move is an attack
        (inrange(p2->animation_frame,
                 active_frames[p2->current_animation].start,
                 active_frames[p2->current_animation].end))) // and it is during its active frames
    {
        if (p2->animation_frame == active_frames[p2->current_animation].start)
        {
            // activate it on the first frame of the animation
            if(p2->paused_frames == 0)
                p2->hitbox_is_active = true;    
        };

        p2->hitbox.x = (p2->main_hurtbox.x) - hitboxes[p2->current_animation].x - hitboxes[p2->current_animation].width;
        p2->hitbox.width = hitboxes[p2->current_animation].width;
        p2->hitbox.y = p2->main_hurtbox.y;
        p2->hitbox.height = p2->main_hurtbox.height;
    }
    else // no hitbox
    {
        p2->hitbox.x = 0;
        p2->hitbox.width = -1;
        p2->hitbox.y = 0;
        p2->hitbox.height = 0;
        p2->hitbox_is_active = false;
    }
    if (is_attack(p2->current_animation))
    {
        p2->move_hurtbox.x = (p2->main_hurtbox.x) - hitboxes[p2->current_animation].x - hitboxes[p2->current_animation].width + 5;
        p2->move_hurtbox.width = hitboxes[p2->current_animation].width;
        p2->move_hurtbox.y = p2->main_hurtbox.y;
        p2->move_hurtbox.height = p2->main_hurtbox.height;
    }
    else
    {
        p2->move_hurtbox.x = 0;
        p2->move_hurtbox.width = -1;
        p2->move_hurtbox.y = 0;
        p2->move_hurtbox.height = 0;
    }
}

int check_hitboxes(player* p1, player* p2)
// check whether a player hit another
// and decide whether a player should be on blockstun or hitstun,
// if hit, take away their health points,
// and if necessary, return the sound that should be played.
{
    bool p1_was_hit = false;
    bool p1_blocked = false;
    bool p2_was_hit = false;
    bool p2_blocked = false;

    if ((boxes_collide(p1->hitbox, p2->main_hurtbox) ||
        boxes_collide(p1->hitbox, p2->move_hurtbox)) && p1->hitbox_is_active && !p2->is_godmode)
        p2_was_hit = true;

    if ((boxes_collide(p2->hitbox, p1->main_hurtbox) ||
        boxes_collide(p2->hitbox, p1->move_hurtbox)) && p2->hitbox_is_active && !p1->is_godmode)
        p1_was_hit = true;
    
    // set flags
    if (p1_was_hit)
    {
        if (p1->is_inputting_block && (is_neutral(p1->current_animation) || is_blocking(p1->current_animation)))
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
        if (p2->is_inputting_block && (is_neutral(p2->current_animation) || is_blocking(p2->current_animation)))
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
            p1->health -= damage[p2->current_animation];
            p1->paused_frames = DEFAULT_STUN + hitstun[p2->current_animation];
            p2->paused_frames = DEFAULT_STUN - hitstun[p2->current_animation];
            
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
            p1->paused_frames = DEFAULT_STUN + blockstun[p2->current_animation];
            p2->paused_frames = DEFAULT_STUN - blockstun[p2->current_animation];
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
        p2->hitbox_is_active = false;
        p2->animation_frame++;
    }

    if(p2_was_hit)
    {
        if (!p2_blocked)
        {
            p2->health -= damage[p1->current_animation];
            p2->paused_frames = DEFAULT_STUN + hitstun[p1->current_animation];
            p1->paused_frames = DEFAULT_STUN - hitstun[p1->current_animation];

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
            p1->paused_frames = DEFAULT_STUN + blockstun[p2->current_animation];
            p2->paused_frames = DEFAULT_STUN - blockstun[p2->current_animation];

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
        p1->hitbox_is_active = false;
        p1->animation_frame++;
    }

    // retval: the sound to be played
    if  (p1_was_hit && !p1_blocked) // p1 was hit
    {
        if (p2->current_animation == dash_punch)
            return medium_hit;
        else
            return light_hit;
    }
    else if (p2_was_hit && !p2_blocked) // p2 was hit
    {
        if (p1->current_animation == dash_punch)
            return medium_hit;
        else
            return light_hit;
    }
    else if (p1_was_hit || p2_was_hit) // someone blocked
        return block;
    else
        return WHIFF; // nothing happened
}