#include "logic.h"

bool boxes_collide(box_t A, box_t B)
// return true if boxes collide
{
    if(A.width == -1 || B.width == -1) // illegal boxes
    {
        return false;
    }

    if(A.x > (B.x + B.width)) return false;
    if((A.x + A.width) < B.x) return false;
    if(A.y > (B.y + B.height)) return false;
    if((A.y + A.height) < B.y) return false;

    return true;
}

void choose_animation(player* p, player* other_p)
// according to input/game state, decide which animation the player will perform
{
    if(p->is_KOd == true) // don't update animation of KOd players
    {
        return;
    }

    bool can_move = false;
    
    if (p->wanted_animation == geneijin)
        // godmode 
        can_move = true;

    if (p->animation_frame >= frames_on_each_animation[p->current_animation])
    // just finished a move, whichever it was
    {
        can_move = true;
        p->animation_frame = 0;
    }

    if (is_neutral(p->current_animation))
        can_move = true;

    if (((p->current_animation == crouching) || is_attack(p->last_animation) ||
         (p->current_animation == low_hitstun) || p->current_animation == block_low) && can_move)
         // some moves need to connect easily with the crouching animation, go directly into it, such as
         // the moves above.
    {
        if (p->wanted_animation == crouching)
        {
            if (is_attack(p->last_animation) || (p->last_animation == low_hitstun) || 
                                                p->last_animation == block_low)
            // connect it directly
                p->current_animation = crouching;

            p->is_standing = false;

            if ((p->animation_sprite_id < 5) && !(is_attack(p->last_animation) ||
                                                 (p->last_animation == low_hitstun) ||
                                                  p->last_animation == block_low));
            // is starting to crouch, just let it be.

            else if (p->animation_sprite_id == (5) || (is_attack(p->last_animation) ||
                                                      (p->last_animation == low_hitstun) ||
                                                       p->last_animation == block_low))
            // has fully crouched OR recovering from animation
            {
                p->last_animation = idle;
                p->animation_frame = (6*INTERVAL); // hardcoded frame when the player is crouching
            }
            else
            // was standing up but decided to go back to crouching
            {
                // reset animation
                p->animation_frame = 0;
            }
        }
    }

    if (can_move)
    {
        // again, details when crouching
        if ((p->current_animation == crouching) && ((p->wanted_animation == idle)))
        {

            if (p->animation_frame == (frames_on_each_animation[crouching] - 1))
            // only switch to idle animation when "standing up" animation is done
            {
                p->current_animation = p->wanted_animation;
                p->animation_frame = 0;
            }
        }
        else if(p->current_animation != p->wanted_animation)
        {
            // switch to animation
            p->current_animation = p->wanted_animation;
            p->animation_frame = 0;
        }
    }
    // force block/stun animation
    else if (is_hitstun(p->wanted_animation) || is_blocking(p->wanted_animation))
    {
        p->current_animation = p->wanted_animation;
        if (p->current_animation != p->wanted_animation)
            p->animation_frame = 0;
    }
    else if (p->current_animation == crLP || p->current_animation == crMK) // crLP and crMK cancel into dash_punch!
    {
        if ((p->animation_frame == active_frames[p->current_animation].end)) // cancel only in the last active frame
        {
            if ((p->wanted_animation == dash_punch) && // only cancel if previous move didnt whiff
                (is_blocking(other_p->current_animation) || is_hitstun(other_p->current_animation)))
            {
                p->current_animation = dash_punch;
                p->animation_frame = 0;
            }
        }
    }
   
    if (p->is_neutral)
        p->is_neutral = true;

    if(is_standing(p))
        p->is_standing = true;
    else if (p->current_animation == crouching && p->animation_sprite_id > (5))
        // standing up
        p->is_standing = true;

    // this is important so when doing command moves (such as crMK and crLP)
    // the move won't repeat itself
    if ((is_attack(p->current_animation) || (p->current_animation == low_hitstun) ||
         p->current_animation == block_low) && (p->current_animation == p->wanted_animation))
    {
        if (p->is_standing){
            p->wanted_animation = idle;
        }
        else if (p->current_animation != dash_punch 
                && p->current_animation != overhead) // if you dash punch or overhead, you have to stand again
        {
            // used so when recovering from an attack, the player won't have to crouch again 
            p->last_animation = p->wanted_animation;
            p->wanted_animation = crouching;
        }
    }
}

int speed_for_player(player* p, player* other_p)
// get the speed for 'p', according to its animation and the other player's animation too.
{
    switch (p->current_animation)
    {
    case walk_forward:
        return PLAYER_SPEED;

    case walk_backwards:
        return -PLAYER_SPEED;

    case dash:
    case dash_punch:
        return PLAYER_SPEED * 1.5;
    
    case backdash:
        return PLAYER_SPEED * -1.1;

    case overhead:
        return PLAYER_SPEED * 0.5;

    case block_low:
    case block_high:
        return -PLAYER_SPEED/2;

    case high_hitstun:
    case low_hitstun:
        return -2*PLAYER_SPEED/3;

    case crLP:
    case crMK:
        // pushback only on block/on hit
        if ((p->is_player1 && // P1 hit P2
            (is_blocking(other_p->current_animation) || is_hitstun(other_p->current_animation))) ||
            (!p->is_player1 && // P2 hit P1 
            (is_blocking(other_p->current_animation) || is_hitstun(other_p->current_animation))))
            
            return -PLAYER_SPEED/2;
        else
            return 0;

    default:
        return 0;
    }
}

void check_movement(player* p1, player* p2)
// update players' position based on their animations
{
    // p1:
    if (p1->paused_frames == 0)
    {
        if (speed_for_player(p1, p2) > 0)
        {
            if (!boxes_collide(default_hurtbox_for_p(p1), default_hurtbox_for_p(p2)) && (p1->x < SCR_MAX))
                p1->x += speed_for_player(p1, p2);

            else if (boxes_collide(default_hurtbox_for_p(p1), default_hurtbox_for_p(p2)))
            {
                if (p2->x < SCR_MAX) // drag the other player along
                {
                    p1->x += speed_for_player(p1, p2)/2;
                    p2->x += speed_for_player(p1, p2)/2;
                }
            }
        }
        else
        {
            if (p1->x > SCR_MIN)
                p1->x += speed_for_player(p1, p2);
        }
    }
    // for p2
    if (p2->paused_frames == 0)
    {
        if (speed_for_player(p2, p1) > 0)
        {
            if (!boxes_collide(default_hurtbox_for_p(p2), default_hurtbox_for_p(p1)) && (p2->x > SCR_MIN))
                p2->x -= speed_for_player(p2, p1);

            else if (boxes_collide(default_hurtbox_for_p(p1), default_hurtbox_for_p(p2)))
            {
                if (p1->x > SCR_MIN) // drag the other player along
                {
                    p1->x -= speed_for_player(p2, p1)/2;
                    p2->x -= speed_for_player(p2, p1)/2;
                }
            }
        }
        else
        {
            if (p2->x < SCR_MAX)
                p2->x -= speed_for_player(p2, p1);
        }
    }
}

int check_ko (player* p1, player* p2)
// check whether a player was KOd.
{
    if(!(p1->is_KOd || p2->is_KOd))
    // don't check it twice
    {
        if (p1->health <= 0)
        {
            p1->is_KOd = true;
            p1->animation_frame = 0;
            p1->current_animation = fall;
        }
        if (p2->health <= 0)
        {
            p2->is_KOd = true;
            p2->animation_frame = 0;
            p2->current_animation = fall;
        }
        if(p1->is_KOd || p2->is_KOd)
            return 1;   
    }
    return 0;
}