#include "input.h"

unsigned char key[ALLEGRO_KEY_MAX]; // used to tell whether a key is being pressed

void input_setup()
{
    memset(key, 0, sizeof(key)); // clear it
}

int check_input(player *p1, player *p2, ALLEGRO_EVENT event)
// return the animation the player wants to execute
// (handles all the input)
{
    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER: // clock ticks

        if(p1->wanted_animation == crMK || p1->wanted_animation == crLP)
            break;

        p1->wanted_animation = idle; // default animation
        p1->is_blocking = false; // by default no one is blocking

        if (key[ALLEGRO_KEY_DOWN])
        {
            p1->wanted_animation = crouching;
        }
        if (key[ALLEGRO_KEY_LEFT]){
            p1->is_blocking = true;
            if (p1->wanted_animation != crouching) // do not walk if crouching
                p1->wanted_animation = walk_backwards;
        }
        else if (key[ALLEGRO_KEY_RIGHT]){
            if (p1->wanted_animation != crouching) // do not walk if crouching
                p1->wanted_animation = walk_forward;
        }
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;

        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        if (event.keyboard.keycode == ALLEGRO_KEY_COMMA)
        {
            p1->wanted_animation = crMK;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_FULLSTOP)
        {
            p1->wanted_animation = crLP;
        }
        else
        {
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        }
        break;

    case ALLEGRO_EVENT_KEY_UP:
        key[event.keyboard.keycode] &= KEY_RELEASED;
        break;
    }

    p2->wanted_animation = idle;


    return 0;
}