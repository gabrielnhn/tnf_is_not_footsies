#include "loops.h"

int main_menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE** sounds)
{
    bool menu_done = false;
    int input;
    int p2_option = IS_CPU;
    while(!menu_done)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            draw_main_menu(p2_option);
            break;

        case ALLEGRO_EVENT_KEY_DOWN: // key pressed
            input = event.keyboard.keycode;

            if (input == ALLEGRO_KEY_Q)
            {
                menu_done = true;
                p2_option = QUIT;
            }
            else if (input == ALLEGRO_KEY_H)
            {
                menu_done = true;
                p2_option = HELP;
            }

            else if (input == ALLEGRO_KEY_ENTER)
                menu_done = true;
            else if (input == ALLEGRO_KEY_A)
                p2_option = IS_CPU;
            else if (input == ALLEGRO_KEY_D)
                p2_option = IS_PLAYER2;

            break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                menu_done = true;
                p2_option = QUIT;
                break;
        }
    }
    // super important, SEGFAULT otherwise:
    al_flush_event_queue(queue);
    return p2_option;
}

int level_menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE** sounds)
{
    int seconds_on_each_level[LEVELS_N];
    get_highscores(seconds_on_each_level);

    bool menu_done = false;
    int input;
    int level = 1;
    while(!menu_done)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            draw_level_menu(level, seconds_on_each_level);
            break;

        case ALLEGRO_EVENT_KEY_DOWN: // key pressed
            input = event.keyboard.keycode;

            if (input == ALLEGRO_KEY_ENTER)
                menu_done = true;
            else if (input == ALLEGRO_KEY_A){
                if (1 < level)
                    level--;
            }
            else if (input == ALLEGRO_KEY_D){
                if (level < LEVELS_N)
                    level++;
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            abort();
            break;
        }
    }
    // super important, SEGFAULT otherwise:
    al_flush_event_queue(queue);
    return level;
}

long match_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue,
                ALLEGRO_BITMAP*** animations, ALLEGRO_BITMAP* stage, 
                ALLEGRO_SAMPLE** sounds, int p2_option, int cpu_level)
{
    // Initial setup:

    bool clock_tick = true; // every time the clock ticks, check game state
    player p1, p2;

    // Match setup:
    input_setup(&p1, &p2);
    animation_setup();
    attacks_setup();
    if (p2_option == IS_CPU)
        autoplayer_setup();

    bool match_over = false;
    int round_number = 1;
    p1.rounds_won = 0;
    p2.rounds_won = 0;
    char const *message;
    long frame_count = 0;

    while (!match_over)
    {
        // Round setup:
        init_players(&p1, &p2);
        bool round_over = false;
        
        // time before round starts: //
        int start = frame_count;
        if (round_number == 1)
            play_sound(sounds, round1);
        else if  (round_number == 2)
            play_sound(sounds, round2);
        else
            play_sound(sounds, final_round);

        while (frame_count < start + ROUND_START_TIMER)
        {
            al_wait_for_event(queue, &event);

            switch (event.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                round_over = true;
                match_over = true;
                break;

            case ALLEGRO_EVENT_TIMER:
                clock_tick = true;
                frame_count++;
            }

            if (clock_tick){
                // update idle animation
                p1.animation_frame++; // update animation frame
                p2.animation_frame++;
                // just so when the game starts, old input is considered
                check_input(&p1, &p2, event, frame_count, p2_option, cpu_level);
                // force idle animation 
                p1.wanted_animation = idle;
                p2.wanted_animation = idle;
                choose_animation(&p1, &p2); 
                choose_animation(&p2, &p1);

                // for p1
                p1.animation_sprite_id = sprite_for_frame(p1.current_animation, p1.animation_frame);
                p1.sprite = animations[p1.current_animation][p1.animation_sprite_id];

                // for p2
                p2.animation_sprite_id = sprite_for_frame(p2.current_animation, p2.animation_frame);
                p2.sprite = animations[p2.current_animation][p2.animation_sprite_id];

                if (round_number == 1)
                    message = "Round 1";
                else if (round_number == 2)
                    message = "Round 2";
                else
                    message = "Final Round";
                draw_match(stage, &p1, &p2, message);
            }
        }
        // Real match: //
        play_sound(sounds, fight);

        while(!round_over)
        {
            // HANDLE INPUT //
            al_wait_for_event(queue, &event);

            switch (event.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                round_over = true;
                match_over = true;
                break;

            case ALLEGRO_EVENT_TIMER:
                clock_tick = true;

            default:
                check_input(&p1, &p2, event, frame_count, p2_option, cpu_level);
                break;
            }

            // PROCESS GAME STATE IN CURRENT FRAME
            message = "Fight!";

            if (clock_tick && al_is_event_queue_empty(queue))
            {
                if (p1.paused_frames > 0)
                    p1.paused_frames--;
                else
                {
                    p1.paused_frames = 0;
                    p1.animation_frame++;
                }

                if (p2.paused_frames > 0)
                    p2.paused_frames--;
                else
                {
                    p2.paused_frames = 0;
                    p2.animation_frame++;
                }
                update_boxes(&p1, &p2); // according to both players' position

                int hitbox_retval = check_hitboxes(&p1, &p2);
                if (hitbox_retval != WHIFF)
                    play_sound(sounds, hitbox_retval);

                if (check_ko(&p1, &p2))
                    play_sound(sounds, KO);

                choose_animation(&p1, &p2); // according to input AND game state
                choose_animation(&p2, &p1);
                
                if (((p1.current_animation == geneijin) && (p1.animation_frame == 0)) ||
                    ((p2.current_animation == geneijin) && (p2.animation_frame == 0)))
                    play_sound(sounds, good);

                // check for movement
                check_movement(&p1, &p2);

                // get the sprite according to the animation

                // for p1
                p1.animation_sprite_id = sprite_for_frame(p1.current_animation, p1.animation_frame);
                p1.sprite = animations[p1.current_animation][p1.animation_sprite_id];

                // for p2
                p2.animation_sprite_id = sprite_for_frame(p2.current_animation, p2.animation_frame);
                p2.sprite = animations[p2.current_animation][p2.animation_sprite_id];

                // check for round over
                if(p1.is_KOd)
                {
                    if (p2.is_KOd)
                        message = "Double K.O.";
                    else
                        message = "P1 K.O.";
                }
                else if (p2.is_KOd)
                    message = "P2 K.O." ;

                draw_match(stage, &p1, &p2, message);

                if (p1.is_KOd)
                {
                    if(p1.animation_frame == 9 * INTERVAL) // when player hits the ground
                        play_sound(sounds, fall_sound);
                    
                    else if(p1.animation_frame > ROUND_END_TIMER)
                    {
                        round_over = true;
                        p2.rounds_won += 1;
                    }
                }
                if (p2.is_KOd) 
                {
                    if (p2.animation_frame == 9 * INTERVAL) // when player hits the ground
                        play_sound(sounds, fall_sound);

                    if (p2.animation_frame > ROUND_END_TIMER)
                    {
                        round_over = true;
                        p1.rounds_won += 1;
                    }
                }

                clock_tick = false;
                frame_count++;
            }
        }
        round_number += 1;
        if (round_number > 3) 
            match_over = true;
        else if ((p1.rounds_won >= 2) || p2.rounds_won >= 2)
            match_over = true;

    }
    return frame_count;
}

void help_menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_SAMPLE** sounds)
{
    bool menu_done = false;
    int input;
    while(!menu_done)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            draw_help_menu();
            break;

        case ALLEGRO_EVENT_KEY_DOWN: // key pressed
            input = event.keyboard.keycode;

            if (input == ALLEGRO_KEY_ENTER)
                menu_done = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            menu_done = true;
            break;
        }
    }
    // super important, SEGFAULT otherwise:
    al_flush_event_queue(queue);
}