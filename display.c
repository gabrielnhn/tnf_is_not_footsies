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
    // draw hurtboxes in blue
    al_draw_filled_rectangle(p1->main_hurtbox.x, p1->main_hurtbox.y,
                             p1->main_hurtbox.x + p1->main_hurtbox.width,
                             p1->main_hurtbox.y + p1->main_hurtbox.height,
                             al_map_rgba_f(0, 0, 0.5, 0.5));

    al_draw_filled_rectangle(p1->move_hurtbox.x, p1->move_hurtbox.y,
                             p1->move_hurtbox.x + p1->move_hurtbox.width,
                             p1->move_hurtbox.y + p1->move_hurtbox.height,
                             al_map_rgba_f(0, 0, 0.5, 0.5));

    al_draw_filled_rectangle(p2->main_hurtbox.x, p2->main_hurtbox.y,
                             p2->main_hurtbox.x + p2->main_hurtbox.width,
                             p2->main_hurtbox.y + p2->main_hurtbox.height,
                             al_map_rgba_f(0, 0, 0.5, 0.5));
    
    al_draw_filled_rectangle(p2->move_hurtbox.x, p2->move_hurtbox.y,
                             p2->move_hurtbox.x + p2->move_hurtbox.width,
                             p2->move_hurtbox.y + p2->move_hurtbox.height,
                             al_map_rgba_f(0, 0, 0.5, 0.5));

    // draw hitboxes in red
    al_draw_filled_rectangle(p1->hitbox.x, p1->hitbox.y,
                             p1->hitbox.x + p1->hitbox.width,
                             p1->hitbox.y + p1->hitbox.height,
                             al_map_rgba_f(0.5, 0, 0, 0.5));
    
    al_draw_filled_rectangle(p2->hitbox.x, p2->hitbox.y,
                             p2->hitbox.x + p2->hitbox.width,
                             p2->hitbox.y + p2->hitbox.height,
                             al_map_rgba_f(0.5, 0, 0, 0.5));
}

void draw_match(ALLEGRO_BITMAP* stage, player* player1, player* player2)
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

void draw_menu()
{
    // clear display
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    // void al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags,
    //                   char const *text)
    // draw options

    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_text(font, al_map_rgba_f(0.5, 0, 0, 0.5), SCR_MIN + 50, HEIGHT + 50, ALLEGRO_ALIGN_CENTRE, "VERSUS CPU");
    
    al_draw_text(font, al_map_rgba_f(0.5, 0, 0, 0.5), SCR_MAX - 50, HEIGHT + 50, ALLEGRO_ALIGN_CENTRE, "VERSUS P1");


    // Print the new display
    al_flip_display();
}