#include <allegro5/allegro5.h>
#define WIDTH 612
#define HEIGHT 235

ALLEGRO_DISPLAY* create_display()
{
    // Display settings
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_get_new_display_flags();
    ALLEGRO_DISPLAY* disp = al_create_display(WIDTH*2, HEIGHT*2);

    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_scale_transform(&trans, 2, 2); // scale by a factor of 2
    al_use_transform(&trans);

    return disp;
}

void destroy_display(ALLEGRO_DISPLAY* disp)
{
    al_destroy_display(disp);
}