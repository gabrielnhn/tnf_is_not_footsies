#include "logic.h"

int check_hitboxes(player* p1, player* p2)
{
    return 0;
}

void choose_animation(player* p)
{
    // int hitbox_retval = check_hitboxes(p1, p2);
    // if (hitbox_retval != 0)
    // {
    //     // histun/blocking animations
    //     return;
    // }

    bool can_move = false;

    if (p->current_animation == crouching)
    {
        if (p->wanted_animation == crouching)
        // continue crouching
        {
            if (p->animation_frame < (6 * INTERVAL) - 1);
            // is starting to crouch, just let it be

            else if (p->animation_sprite_id == (5))
            // has fully crouched
            {
                p->animation_frame = (6*INTERVAL); // hardcoded sprite when Yun is crouching
            }
            else
            // was standing up but decided to go back to crouching
            {
                p->animation_frame = 0;
            }
        }
    }

    if (p->animation_frame >= frames_on_each_animation[p->current_animation])
    // finished a move
    {
        can_move = true;
        p->animation_frame = 0;
    }

    if (is_neutral(p->current_animation))
        can_move = true;

    if (can_move)
    {
        // again, details when crouching
        if ((p->current_animation == crouching) && ((p->wanted_animation == idle)))
        {
            if (p->animation_frame == (frames_on_each_animation[crouching] - 1))
            {
                p->current_animation = p->wanted_animation;
                p->animation_frame = 0;
            }
        }
        else if(p->current_animation != p->wanted_animation)
        {
            p->current_animation = p->wanted_animation;
            p->animation_frame = 0;
        }

        if (is_neutral(p->current_animation))
            p->is_neutral = true;

    }

}