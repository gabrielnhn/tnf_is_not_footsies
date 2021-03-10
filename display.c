#include "display.h"

ALLEGRO_DISPLAY* create_display()
{
    // Display settings
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_get_new_display_flags();
    ALLEGRO_DISPLAY* disp = al_create_display(WIDTH*SCALE, HEIGHT*SCALE);

    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_scale_transform(&trans, SCALE, SCALE); // scale by a factor of SCALE
    al_use_transform(&trans);

    return disp;
}

void destroy_display(ALLEGRO_DISPLAY* disp)
{
    al_destroy_display(disp);
}


void draw_boxes(player* p1, player* p2)
{
    // draw main hurtboxes in blue
    al_draw_filled_rectangle(p1->main_hurtbox.x, p1->main_hurtbox.y,
                             p1->main_hurtbox.x + p1->main_hurtbox.width,
                             p1->main_hurtbox.y + p1->main_hurtbox.height,
                             al_map_rgba_f(0, 0, 0.5, 0.5));

    al_draw_filled_rectangle(p2->main_hurtbox.x, p2->main_hurtbox.y,
                             p2->main_hurtbox.x + p2->main_hurtbox.width,
                             p2->main_hurtbox.y + p2->main_hurtbox.height,
                             al_map_rgba_f(0, 0, 0.5, 0.5));
}

void draw_display(ALLEGRO_BITMAP* stage, player* player1, player* player2)
{
    // clear display
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    // draw stage
    al_draw_bitmap(stage, -220, -220, 0);

    //draw player sprites
    al_draw_bitmap(player1->sprite, player1->x, PLAYER_HEIGHT, ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(player2->sprite, player2->x, PLAYER_HEIGHT, 0);

    draw_boxes(player1, player2);

    // Print the new display
    al_flip_display();
}
