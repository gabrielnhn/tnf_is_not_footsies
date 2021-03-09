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
    // Initialize ALLEGRO funcionalities
    al_init();
    al_install_keyboard();

    // 60 FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    // Weird ass font
    ALLEGRO_FONT* font = al_create_builtin_font();

    // Display module
    ALLEGRO_DISPLAY* disp = create_display();

    // We're going to use images
    al_init_image_addon();

    // Stage image
    ALLEGRO_BITMAP* stage = al_load_bitmap("animation/stage2.png");
    must_init(stage, "Stage");

    // Character image
    // char path[STR_MAX];

    ALLEGRO_BITMAP*** animations;
    animations = load_sprites();

    // Allegro "Events" are interruptions to be handled
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Music module
    ALLEGRO_AUDIO_STREAM* music =  play_music("music/SFVRashid.opus");

    // Initial setup

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    player p1, p2;

    p1.x = 50;
    p2.x = WIDTH - 300;

    p1.current_animation = idle;
    p2.current_animation = idle;
    p1.animation_frame = 0;
    p2.animation_frame = 0;

    input_setup();
    animation_setup();

    long frame_count = 0;
    bool done = false;
    // bool decreasing;
    while(!done)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            check_input(&p1, &p2, event);
            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
           check_input(&p1, &p2, event);

            if(event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
                break;
        
        case ALLEGRO_EVENT_KEY_UP:
            check_input(&p1, &p2, event);
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }
 
        if(redraw && al_is_event_queue_empty(queue)) // no inputs to handle
        {
            p1.animation_frame++;
            p2.animation_frame++;

            choose_animation(&p1);
            choose_animation(&p2);

            // for p1
            // p1.animation_sprite_id = sprite_for_frame(p1.current_animation, frame_count % frames_on_each_animation[p1.current_animation]);
            p1.animation_sprite_id = sprite_for_frame(p1.current_animation, p1.animation_frame);
            printf("%d[%d]\n", p1.current_animation, p1.animation_frame);

            p1.sprite = animations[p1.current_animation][p1.animation_sprite_id];
            // printf("problems\n");

            // for p2
            // p2.animation_sprite_id = sprite_for_frame(p2.current_animation, frame_count % frames_on_each_animation[p2.current_animation]);
            p2.animation_sprite_id = sprite_for_frame(p2.current_animation, p2.animation_frame);

            p2.sprite = animations[p2.current_animation][p2.animation_sprite_id];

            draw_display(stage, &p1, &p2);

            redraw = false;
            frame_count++;
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