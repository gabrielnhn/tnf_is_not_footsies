#include "display.h"

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


void draw_display(ALLEGRO_BITMAP* stage, player* player1, player* player2)
{
    // clear display
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    // draw stage
    al_draw_bitmap(stage, 0, 0, 0);

    al_draw_bitmap(player1->sprite, player1->x, PLAYER_HEIGHT, ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(player2->sprite, player2->x, PLAYER_HEIGHT, 0);

    // Print the new display
    al_flip_display();
}