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
#include "loops.h"
#include "sounds.h"

int main()
{
    // Initial Setup:

    // Initialize ALLEGRO funcionalities
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "allegro keyboard");

    // Run the game on 60 FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "allegro timer");


    // Display module
    ALLEGRO_DISPLAY* disp = create_display();
    must_init(disp, "display");

    must_init(al_init_primitives_addon(), "primitives addon");
    must_init(al_init_image_addon(), "image addon");

    // Images:
    ALLEGRO_BITMAP* stage = al_load_bitmap("resources/animation/stage4.png");
    must_init(stage, "Stage");

    ALLEGRO_BITMAP*** animations; // 2d array of bitmap pointers
    animations = load_sprites();

    // Music 
    ALLEGRO_AUDIO_STREAM* music =  play_music("resources/music/SFVGuile.opus");
    must_init(music, "music");

    // Sounds
    ALLEGRO_SAMPLE** sounds = load_sounds();
    must_init(sounds, "sounds");

    // Allegro "Events" are interruptions to be handled
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "allegro queue");

    ALLEGRO_EVENT event;
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    // GAME/MENU:

    long frame_count;
    int menu_option = 0;
    while (menu_option != QUIT)
    {
        menu_option = main_menu_loop(event, queue, sounds);

        if (menu_option == HELP)
            help_menu_loop(event, queue, sounds);

        int cpu_level = 0;
        if (menu_option == IS_CPU)
            cpu_level = level_menu_loop(event, queue, sounds);

        if ((menu_option == IS_CPU && cpu_level != -1) || menu_option == IS_PLAYER2)
            frame_count = match_loop(event, queue, animations, stage, sounds, menu_option, cpu_level);
        
        if (menu_option == IS_CPU && cpu_level != -1)
            check_for_highscore(cpu_level, frame_count);
    }

    // Game over, destroy everything we made
    destroy_music(music);

    destroy_sounds(sounds);

    al_destroy_bitmap(stage);
    destroy_sprites(animations);

    destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}