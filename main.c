#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "music.c"
#include "display.c"

#define STR_MAX 100

void must_init(bool test, const char *description)
// Used to initialize modules and immediately test whether they work
{
    if(test) return;
    printf("couldn't initialize %s\n", description);
    exit(1);
}

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
    ALLEGRO_BITMAP* yun;
    char yun_path[STR_MAX];
    
    // Allegro "Events" are interruptions to be handled
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Music module
    ALLEGRO_AUDIO_STREAM* music =  play_music("music/SFVRashid.opus");

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    ALLEGRO_TRANSFORM trans;

    int i = 0;
    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if(redraw && al_is_event_queue_empty(queue)) // no events to handle
        {
            // clear display
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            // draw stage
            al_draw_bitmap(stage, 0, 0, 0);

            // alternate Yun idle animation sprites
            int a = i / 2; // change sprites every 2 frames
            int j = (a%11) + 1; // sprites vary from 1 to 12
            i++;
            sprintf(yun_path, "animation/1-idle/%d.png", j);
            yun = al_load_bitmap(yun_path);
            must_init(yun, "Yun");
            al_draw_bitmap(yun, 50, 50, 0);

            // Print the new display
            al_flip_display();

            redraw = false;
        }
    }

    // Game over, destroy everything we made
    destroy_music(music);

    al_destroy_font(font);
    destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}