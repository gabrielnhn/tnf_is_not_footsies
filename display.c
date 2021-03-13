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

void draw_match(ALLEGRO_BITMAP* stage, player* player1, player* player2, char const* message)
{
    // printf("clearing\n");
    // clear display
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    // printf("stage\n");
    // draw stage
    al_draw_bitmap(stage, -220, -220, 0);

    // printf("sprites\n");
    //draw player sprites
    al_draw_bitmap(player1->sprite, player1->x, PLAYER_HEIGHT, ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(player2->sprite, player2->x, PLAYER_HEIGHT, 0);

    // printf("HUD\n");
    // draw HUD
    ALLEGRO_FONT* font = al_create_builtin_font();
    char p1_HP[STR_MAX], p2_HP[STR_MAX];
    char p1_Rounds[STR_MAX], p2_Rounds[STR_MAX];
    sprintf(p1_HP, "%d HP", player1->health);
    sprintf(p2_HP, "%d HP", player2->health);
    sprintf(p1_Rounds, "%d round(s)", player1->rounds_won);
    sprintf(p2_Rounds, "%d round(s)", player2->rounds_won); 

    al_draw_text(font, al_map_rgb_f(0, 1, 0), 100, 1*HEIGHT/12, ALLEGRO_ALIGN_CENTER, p1_HP);
    al_draw_text(font, al_map_rgb_f(0, 1, 0), 100, 2*HEIGHT/12, ALLEGRO_ALIGN_CENTER, p1_Rounds);
    al_draw_text(font, al_map_rgb_f(0, 1, 0), WIDTH - 100, 1*HEIGHT/12, ALLEGRO_ALIGN_CENTER, p2_HP);
    al_draw_text(font, al_map_rgb_f(0, 1, 0), WIDTH - 100, 2*HEIGHT/12, ALLEGRO_ALIGN_CENTER, p2_Rounds);

    // printf("message?\n");
    if(strcmp(message, "") != 0)
    {
        al_draw_text(font, al_map_rgb_f(1, 0, 0), WIDTH/2, HEIGHT/5, ALLEGRO_ALIGN_CENTER, message);
    }

    // draw_boxes(player1, player2);

    // Print this new display
    // printf("flip\n");
    al_flip_display();
}

void draw_menu(int option)
{
    // clear display
    al_clear_to_color(al_map_rgb_f(1, 1, 1));
    
    // void al_draw_text(const ALLEGRO_FONT *font, ALLEGRO_COLOR color, float x, float y, int flags,
    //                   char const *text)
    // draw options

    char* opt1_str = "VERSUS CPU";
    char* opt2_str = "VERSUS P2";


    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), 100, HEIGHT/2, ALLEGRO_ALIGN_CENTER, opt1_str);
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH - 100, HEIGHT/2, ALLEGRO_ALIGN_CENTER, opt2_str);

    int text_x, text_y, text_width, text_height;
    if (option == 1)
    {
        al_get_text_dimensions(font, opt2_str, &text_x, &text_y, &text_width, &text_height);
        al_draw_rectangle(100 - MENU_RECT_BORDER - text_width/2, HEIGHT/2 - MENU_RECT_BORDER,
                          100 + text_width/2 + MENU_RECT_BORDER, HEIGHT/2 + text_height + MENU_RECT_BORDER,
                          al_map_rgb_f(0, 1, 0), 3);
    }
    else // option 2
    {
        al_get_text_dimensions(font, opt1_str, &text_x, &text_y, &text_width, &text_height);
        al_draw_rectangle(WIDTH - 100 - MENU_RECT_BORDER - text_width/2, HEIGHT/2 - MENU_RECT_BORDER,
                          WIDTH - 100 + text_width/2 + MENU_RECT_BORDER, HEIGHT/2 + text_height + MENU_RECT_BORDER,
                          al_map_rgb_f(0, 1, 0), 3);
    }

    //     void al_draw_rectangle(float x1, float y1, float x2, float y2,
    //    ALLEGRO_COLOR color, float thickness)

    // Print the new display
    al_flip_display();
}