#include "match.h"
    
void menu_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue)
{
    bool menu_done = false;
    int input;
    int option = 1;
    while(!menu_done)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            draw_menu(option);
            break;

        case ALLEGRO_EVENT_KEY_DOWN: // key pressed
            input = event.keyboard.keycode;

            if (input == ALLEGRO_KEY_ENTER)
                menu_done = true;
            else if (input == ALLEGRO_KEY_A)
                option = 1;
            else if (input == ALLEGRO_KEY_D)
                option = 2;

            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            abort();
            break;
        }
    }
    // super important, SEGFAULT otherwise:
    al_flush_event_queue(queue);
}


void match_loop(ALLEGRO_EVENT event, ALLEGRO_EVENT_QUEUE* queue,
                ALLEGRO_BITMAP*** animations, ALLEGRO_BITMAP* stage)
{
    bool clock_tick = true; // every time the clock ticks, check game state
    long frame_count = 0;
    player p1, p2;
    init_players(&p1, &p2);

    input_setup(&p1, &p2);
    animation_setup();
    attacks_setup();

    bool game_over = false;
    while(!game_over)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            check_input(&p1, &p2, event, frame_count);
            clock_tick = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN: // key pressed
           check_input(&p1, &p2, event, frame_count);

            if(event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                break;
        
        case ALLEGRO_EVENT_KEY_UP: // key released
            check_input(&p1, &p2, event, frame_count);
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            game_over = true;
            break;
        }
 
        if(clock_tick && al_is_event_queue_empty(queue))
        // PROCESS GAME STATE IN CURRENT FRAME
        {
            if(p1.paused_frames > 0)
                p1.paused_frames--;
            else
                p1.animation_frame++;
            
            if(p2.paused_frames > 0)
                p2.paused_frames--;
            else
                p2.animation_frame++;

            update_boxes(&p1, &p2); // according to both players' position

            p2.is_blocking = true;

            // printf("%d\n",check_hitboxes(&p1, &p2));
            check_hitboxes(&p1, &p2);

            choose_animation(&p1); // according to input AND game state
            choose_animation(&p2);

            // check for movement
            check_movement(&p1, &p2);

            // get the sprite according to the animation

            // for p1
            p1.animation_sprite_id = sprite_for_frame(p1.current_animation, p1.animation_frame);
            p1.sprite = animations[p1.current_animation][p1.animation_sprite_id];

            // for p2
            p2.animation_sprite_id = sprite_for_frame(p2.current_animation, p2.animation_frame);
            // printf("%d %d\n", p2.animation_sprite_id, p2.animation_frame);
            p2.sprite = animations[p2.current_animation][p2.animation_sprite_id];

            draw_match(stage, &p1, &p2);

            clock_tick = false;
            frame_count++;

            
            // print_array(p1.input_buffer, p1.buffer_length);
        }
    }
}
