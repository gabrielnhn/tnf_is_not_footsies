#include "display.h"

ALLEGRO_DISPLAY* create_display()
{
    // Create display
    ALLEGRO_DISPLAY* disp = al_create_display(WIDTH*SCALE, HEIGHT*SCALE);

    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_scale_transform(&trans, SCALE, SCALE); // scale it by a factor of $SCALE
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
    // clear display
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    // draw stage
    al_draw_bitmap(stage, -220, -220, 0);

    //draw player sprites
    al_draw_bitmap(player1->sprite, player1->x, PLAYER_HEIGHT, ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(player2->sprite, player2->x, PLAYER_HEIGHT, 0);

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

    if(strcmp(message, "") != 0)
    {
        al_draw_text(font, al_map_rgb_f(1, 0, 0), WIDTH/2, HEIGHT/5, ALLEGRO_ALIGN_CENTER, message);
    }

    // draw_boxes(player1, player2);

    // Print this new display
    al_flip_display();
    al_destroy_font(font);
}

void draw_main_menu(int option)
{
    // clear display
    al_clear_to_color(al_map_rgb_f(0, 0.7, 0.7));
    
    // draw options
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_draw_text(font, al_map_rgb_f(1, 1, 0), WIDTH/2, HEIGHT/10, ALLEGRO_ALIGN_CENTER, "TNF is Not Footsies!");

    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 2*HEIGHT/10, ALLEGRO_ALIGN_CENTER,
                "(Use 'A' and 'D' to navigate)");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 3*HEIGHT/10, ALLEGRO_ALIGN_CENTER,
                "(Press 'ENTER' to select)");


    al_draw_text(font, al_map_rgb_f(1, 1, 1), 100, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "VERSUS CPU");
    al_draw_text(font, al_map_rgb_f(1, 1, 1), WIDTH - 100, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "VERSUS P2");

    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 8*HEIGHT/10, ALLEGRO_ALIGN_CENTER, "(Press 'h' for help)");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 9*HEIGHT/10, ALLEGRO_ALIGN_CENTER, "(Press 'q' to quit)");

    int text_x, text_y, text_width, text_height;
    if (option == 1)
    {
        al_get_text_dimensions(font, "VERSUS CPU", &text_x, &text_y, &text_width, &text_height);
        al_draw_rectangle(100 - MENU_RECT_BORDER - text_width/2, HEIGHT/2 - MENU_RECT_BORDER,
                          100 + text_width/2 + MENU_RECT_BORDER, HEIGHT/2 + text_height + MENU_RECT_BORDER,
                          al_map_rgb_f(0, 1, 0), 3);
    }
    else // option 2
    {
        al_get_text_dimensions(font, "VERSUS P2", &text_x, &text_y, &text_width, &text_height);
        al_draw_rectangle(WIDTH - 100 - MENU_RECT_BORDER - text_width/2, HEIGHT/2 - MENU_RECT_BORDER,
                          WIDTH - 100 + text_width/2 + MENU_RECT_BORDER, HEIGHT/2 + text_height + MENU_RECT_BORDER,
                          al_map_rgb_f(0, 1, 0), 3);
    }

    // Print the new display
    al_flip_display();
    al_destroy_font(font);
}

void draw_level_menu(int level, int* seconds_on_each)
{
    // clear display
    al_clear_to_color(al_map_rgb_f(0, 0.7, 0.7));
    
    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 2*HEIGHT/9, ALLEGRO_ALIGN_CENTER,
                "CPU Level:");

    char str[STR_MAX];
    for(int i = 1; i <= LEVELS_N; i++)
    {
        sprintf(str, "%d", i);
        al_draw_text(font, al_map_rgb_f(1, 1, 1), BORDER_BETWEEN_LEVELS + (i-1)*WIDTH/LEVELS_N, HEIGHT/2, ALLEGRO_ALIGN_CENTER, str);
    }

    // draw selection rectangle
    int text_width, text_height;
    text_width =  al_get_text_width(font, "0");
    text_height = al_get_font_line_height(font);

    al_draw_rectangle(BORDER_BETWEEN_LEVELS + (level-1)*WIDTH/LEVELS_N - MENU_RECT_BORDER - text_width/2, HEIGHT/2 - MENU_RECT_BORDER,
                        BORDER_BETWEEN_LEVELS + (level-1)*WIDTH/LEVELS_N + text_width/2 + MENU_RECT_BORDER, HEIGHT/2 + text_height + MENU_RECT_BORDER,
                        al_map_rgb_f(0, 1, 0), 3);
    
    if (seconds_on_each[level - 1] != -1)
        sprintf(str, "Highscore for %d: %dsec", level, seconds_on_each[level - 1]);
    else
        sprintf(str, "Highscore for %d: Null", level);

    al_draw_text(font, al_map_rgb_f(1, 0, 0), WIDTH/2, HEIGHT/2 + text_height*4, ALLEGRO_ALIGN_CENTER, str);

    // Print the new display
    al_flip_display();
    al_destroy_font(font);
}

void draw_help_menu()
{
    // clear display
    al_clear_to_color(al_map_rgb_f(0, 0.7, 0.7));
    
    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_text(font, al_map_rgb_f(0.5, 0.5, 0), 1*WIDTH/4, 1*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"P1 Inputs:");
    al_draw_text(font, al_map_rgb_f(0.5, 0.5, 0), 1*WIDTH/4, 2*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Left: A");
    al_draw_text(font, al_map_rgb_f(0.5, 0.5, 0), 1*WIDTH/4, 3*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Down: S");
    al_draw_text(font, al_map_rgb_f(0.5, 0.5, 0), 1*WIDTH/4, 4*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Right: D");
    al_draw_text(font, al_map_rgb_f(0.5, 0.5, 0), 1*WIDTH/4, 5*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Punch: B");
    al_draw_text(font, al_map_rgb_f(0.5, 0.5, 0), 1*WIDTH/4, 6*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Kick: V");

    al_draw_text(font, al_map_rgb_f(0.5, 0, 0.5), 3*WIDTH/4, 1*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"P2 Inputs:");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0.5), 3*WIDTH/4, 2*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Left: LeftKey");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0.5), 3*WIDTH/4, 3*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Down: DownKey");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0.5), 3*WIDTH/4, 4*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Right: RightKey");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0.5), 3*WIDTH/4, 5*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Punch: Comma(,)");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0.5), 3*WIDTH/4, 6*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Kick: FullStop(.)");

    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 7*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Read the README file for more information!");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 8*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"Author: Gabriel Nascarella Hishida");
    al_draw_text(font, al_map_rgb_f(0.5, 0, 0), WIDTH/2, 9*HEIGHT/10, ALLEGRO_ALIGN_CENTER,"(Press Enter to quit help menu)");

    // Print the new display
    al_flip_display();
    al_destroy_font(font);
}
