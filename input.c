#include "input.h"

unsigned char key[ALLEGRO_KEY_MAX]; // used to tell whether a key is being pressed

void input_setup(player* p1, player* p2)
// clear up input systems
{
    memset(key, 0, sizeof(key));
    memset(p1->input_buffer, 0, sizeof(p1->input_buffer));
    memset(p2->input_buffer, 0, sizeof(p2->input_buffer));
    p1->buffer_length = 0;
    p2->buffer_length = 0;
    p1->last_input_frame = 0;
    p2->last_input_frame = 0;
}

void check_input(player *p1, player *p2, ALLEGRO_EVENT event, long frame_count,
                int p2_input_method, int cpu_level)
// control each players' input buffer,
// set the animation the players want to execute,
// and also sets up control variables such as '.is_inputting_block' or '.is_godmode'
{
    switch (event.type)
    {
        case ALLEGRO_EVENT_TIMER: // clock ticks
            // according to key[] and p->input_buffer[], decide which animation to play

            // different animations DO have priority!
            p1->wanted_animation = idle; // default animation
            p1->is_inputting_block = false; // by default no one is blocking

            p2->wanted_animation = idle; 
            p2->is_inputting_block = false; 

            // FOR PLAYER 1 // 

            // check for godmode
            if ((p1->buffer_length > 4) &&
                (p1->input_buffer[p1->buffer_length - 1] == p1PUNCH) && // just pressed PUNCH
                (p1->input_buffer[p1->buffer_length - 2] == p1KICK) && // just pressed KICK
                (p1->input_buffer[p1->buffer_length - 3] == p1RIGHT) && // was pressing forward
                (p1->input_buffer[p1->buffer_length - 4] == p1PUNCH) && // just pressed PUNCH
                (p1->input_buffer[p1->buffer_length - 5] == p1PUNCH))// just pressed PUNCH

            {
                // 👊+👊+→+👟+👊
                p1->wanted_animation = geneijin;
                p1->is_godmode = true;
            }

            // check for dash punch
            else if ((p1->buffer_length > 2) &&
                (p1->input_buffer[p1->buffer_length - 1] == p1PUNCH) && // just pressed PUNCH
                (p1->input_buffer[p1->buffer_length - 2] == p1RIGHT) && // was pressing forward
                ((p1->input_buffer[p1->buffer_length - 3] == p1DOWN) || !p1->is_standing)) // pressed DOWN a short time ago
            {
                // ↓→+👊
                p1->wanted_animation = dash_punch;
            }

            // check for overhead
            else if ((p1->buffer_length > 0) &&
                     (p1->input_buffer[p1->buffer_length - 1] == p1KICK) &&// just pressed KICK
                     (key[ALLEGRO_KEY_D])) // is holding forward
            {
                // →+👟
                p1->wanted_animation = overhead;
            }
            
            // check for dash
            else if ((p1->buffer_length > 1) &&
                     (p1->input_buffer[p1->buffer_length - 1] == p1RIGHT) &&
                     (p1->input_buffer[p1->buffer_length - 2] == p1RIGHT)) // just pressed RIGHT twice
            {
                // →+→
                p1->wanted_animation = dash;
            }

            // check for backdash
            else if ((p1->buffer_length > 1) &&
                     (p1->input_buffer[p1->buffer_length - 1] == p1LEFT) &&
                     (p1->input_buffer[p1->buffer_length - 2] == p1LEFT)) // just pressed LEFT twice
            {
                // ←+←
                p1->wanted_animation = backdash;
            }

            // check for crMK
            else if ((p1->buffer_length > 0) &&
                     (p1->input_buffer[p1->buffer_length - 1] == p1KICK)) // just pressed KICK
            {
                // 👟
                p1->wanted_animation = crMK;
            }

            // check for crLP
            else if ((p1->buffer_length > 0) &&
                     (p1->input_buffer[p1->buffer_length - 1] == p1PUNCH)) // just pressed KICK
            {
                // 👊
                p1->wanted_animation = crLP;
            }

            // no special commands, just movement:

            else if(key[ALLEGRO_KEY_S])
            {
                p1->wanted_animation = crouching;
                if (key[ALLEGRO_KEY_A])
                    p1->is_inputting_block = true;
            }
            else if (key[ALLEGRO_KEY_A])
            {
                p1->is_inputting_block = true;
                p1->wanted_animation = walk_backwards;
            }
            else if (key[ALLEGRO_KEY_D])
            {
                if (p1->wanted_animation != crouching)
                    p1->wanted_animation = walk_forward;
            }

            // FOR PLAYER2:

            if(p2_input_method == IS_CPU)
                get_autoplayer_input(p1, p2, cpu_level);

            else // p2 == PLAYER2
            {
                // check for godmode
                if ((p2->buffer_length > 4) &&
                    (p2->input_buffer[p2->buffer_length - 1] == p2PUNCH) && // just pressed PUNCH
                    (p2->input_buffer[p2->buffer_length - 2] == p2KICK) && // just pressed KICK
                    (p2->input_buffer[p2->buffer_length - 3] == p2LEFT) && // was pressing forward
                    (p2->input_buffer[p2->buffer_length - 4] == p2PUNCH) && // just pressed PUNCH
                    (p2->input_buffer[p2->buffer_length - 5] == p2PUNCH))// just pressed PUNCH

                {
                    // 👊+👊+→+👟+👊
                    p2->wanted_animation = geneijin;
                    p2->is_godmode = true;
                }
                // check for dash punch
                else if ((p2->buffer_length > 2) &&
                    (p2->input_buffer[p2->buffer_length - 1] == p2PUNCH) && // just pressed PUNCH
                    (p2->input_buffer[p2->buffer_length - 2] == p2LEFT) && // was pressing forward
                    ((p2->input_buffer[p2->buffer_length - 3] == p2DOWN) || !p2->is_standing)) // pressed DOWN a short time ago
                {
                    // ↓→+👊
                    p2->wanted_animation = dash_punch;
                }

                // check for overhead
                else if ((p2->buffer_length > 0) &&
                        (p2->input_buffer[p2->buffer_length - 1] == p2KICK) &&// just pressed KICK
                        (key[ALLEGRO_KEY_LEFT])) // is holding forward
                {
                    // →+👟
                    p2->wanted_animation = overhead;
                }
                
                // check for dash
                else if ((p2->buffer_length > 1) &&
                        (p2->input_buffer[p2->buffer_length - 1] == p2LEFT) &&
                        (p2->input_buffer[p2->buffer_length - 2] == p2LEFT)) // just pressed RIGHT twice
                {
                    // →+→
                    p2->wanted_animation = dash;
                }

                // check for backdash
                else if ((p2->buffer_length > 1) &&
                        (p2->input_buffer[p2->buffer_length - 1] == p2RIGHT) &&
                        (p2->input_buffer[p2->buffer_length - 2] == p2RIGHT)) // just pressed LEFT twice
                {
                    // ←+←
                    p2->wanted_animation = backdash;
                }

                // check for crMK
                else if ((p2->buffer_length > 0) &&
                        (p2->input_buffer[p2->buffer_length - 1] == p2KICK)) // just pressed KICK
                {
                    // 👟
                    p2->wanted_animation = crMK;
                }

                // check for crLP
                else if ((p2->buffer_length > 0) &&
                        (p2->input_buffer[p2->buffer_length - 1] == p2PUNCH)) // just pressed KICK
                {
                    // 👊
                    p2->wanted_animation = crLP;
                }

                // no special commands, just movement:

                else if(key[ALLEGRO_KEY_DOWN])
                {
                    p2->wanted_animation = crouching;
                    if (key[ALLEGRO_KEY_RIGHT])
                        p2->is_inputting_block = true;
                }
                else if (key[ALLEGRO_KEY_RIGHT])
                {
                    p2->is_inputting_block = true;
                    p2->wanted_animation = walk_backwards;
                }
                else if (key[ALLEGRO_KEY_LEFT])
                {
                    if (p2->wanted_animation != crouching)
                        p2->wanted_animation = walk_forward;
                }
            }

            // Needed to keep the input system working

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

            // reset player buffers if needed:
            if (frame_count > (p1->last_input_frame + BUFFER_TIMER))
            {
                p1->buffer_length = 0; // reset buffer
            }
            if (frame_count > (p2->last_input_frame + BUFFER_TIMER))
            {
                p2->buffer_length = 0; // reset buffer
            }

            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            // store it in the array (useful for directional inputs)
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            
            // proceed to store it in the buffer
            int input;
            int p;
            switch (event.keyboard.keycode)
            {
                // P1:
                case ALLEGRO_KEY_V: // p1 kick
                    p = 1;
                    input = p1KICK;
                    break;

                case ALLEGRO_KEY_B: // p1 punch
                    p = 1;
                    input = p1PUNCH;
                    break;

                case ALLEGRO_KEY_S:
                    p = 1;
                    input = p1DOWN;
                    break;

                case ALLEGRO_KEY_A:
                    p = 1;
                    input = p1LEFT;
                    break;

                case ALLEGRO_KEY_D:
                    p = 1;
                    input = p1RIGHT;
                    break;

                // P2:

                case ALLEGRO_KEY_FULLSTOP: // p2 kick
                    p = 2;
                    input = p2KICK;
                    break;

                case ALLEGRO_KEY_COMMA: // p2 punch
                    p = 2;
                    input = p2PUNCH;
                    break;

                case ALLEGRO_KEY_DOWN:
                    p = 2;
                    input = p2DOWN;
                    break;

                case ALLEGRO_KEY_LEFT:
                    p = 2;
                    input = p2LEFT;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    p = 2;
                    input = p2RIGHT;
                    break;
            }
            if (p == 1)
            {
                p1->last_input_frame = frame_count;
                p1->input_buffer[p1->buffer_length] = input;
                p1->buffer_length++;
            }
            else // player 2
            {
                p2->last_input_frame = frame_count;
                p2->input_buffer[p2->buffer_length] = input;
                p2->buffer_length++;
            }

            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;
    }

}