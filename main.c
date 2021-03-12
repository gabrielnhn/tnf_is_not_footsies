#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "music.h"
#include "display.h"
#include "animation.h"
#include "utils.h"
#include "input.h"
#include "logic.h"


int main()
{
    // Initial Setup:

    // Initialize ALLEGRO funcionalities
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "allegro keyboard");

    // 60 FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "allegro timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "allegro queue");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "allegro font");

    // Display module
    ALLEGRO_DISPLAY
    // draw_boxes(player1, player2);* disp = create_display();
    must_init(disp, "display");

    must_init(al_init_primitives_addon(), "primitives addon");
    must_init(al_init_image_addon(), "image addon");

    // Stage image
    ALLEGRO_BITMAP* stage = al_load_bitmap("animation/stage4.png");
    must_init(stage, "Stage");

    ALLEGRO_BITMAP*** animations; // 2d array of bitmap pointers
    animations = load_sprites();

    // Allegro "Events" are interruptions to be handled
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Music module
    ALLEGRO_AUDIO_STREAM* music =  play_music("music/SFVGuile.opus");
    must_init(music, "music");

    // Initial game setup

    bool clock_tick = true; // every time the clock ticks, check game state
    al_start_timer(timer);
    ALLEGRO_EVENT event;
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

    // Game over, destroy everything we made
    destroy_music(music);

    al_destroy_bitmap(stage);
    destroy_sprites(animations);

    al_destroy_font(font);
    destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}