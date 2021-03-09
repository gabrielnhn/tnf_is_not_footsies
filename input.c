#include "input.h"

unsigned char key[ALLEGRO_KEY_MAX];

void input_setup()
{
    memset(key, 0, sizeof(key));
}

int check_input(player *p1, player *p2, ALLEGRO_EVENT event)
// return the animation the player wants to execute
// (handles all the input)
{
    int retval = 0;
    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER: // clock ticks

        if(p1->wanted_animation == crMK || p1->wanted_animation == crLP)
            break;

        p1->wanted_animation = idle; // default animation

        if (key[ALLEGRO_KEY_DOWN])
            p1->wanted_animation = crouching;

        else if (key[ALLEGRO_KEY_LEFT])
            p1->wanted_animation = walk_backwards;

        else if (key[ALLEGRO_KEY_RIGHT])
            p1->wanted_animation = walk_forward;

        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;

        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        if (event.keyboard.keycode == ALLEGRO_KEY_COMMA)
        {
            // printf("crMK\n");
            p1->wanted_animation = crMK;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_FULLSTOP)
        {
            // printf("crLP\n");
            p1->wanted_animation = crLP;
        }
        else
        {
            // printf("Other\n");
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        }
        break;

    case ALLEGRO_EVENT_KEY_UP:
        key[event.keyboard.keycode] &= KEY_RELEASED;
        break;
    }
    return retval;
}