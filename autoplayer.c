#include "autoplayer.h"

void autoplayer_setup()
{
    // setup for random values
    time_t t;
    srand((unsigned) time(&t));
}

int autoplayer_count;

void get_autoplayer_input(player* p1, player* p2, int cpu_level)
{
    switch (cpu_level)
    {
    case 1:
        // just blocking high
        p2->wanted_animation = walk_backwards;
        p2->is_inputting_block = true;
        break;
    
    case 2:
        // just blocking low
        p2->wanted_animation = crouching;
        p2->is_inputting_block = true;
        break;

    case 3:
        // spammer (hit-confirm)
        p2->wanted_animation = crMK;
        if (is_hitstun(p1->current_animation))
            p2->wanted_animation = dash_punch;
        break;

    case 4:
        // risky
        autoplayer_count++;
        if (autoplayer_count % AUTOP_INTERVAL == 0)
            p2->wanted_animation = dash_punch;
        else
            p2->wanted_animation = crouching;
        p2->is_inputting_block = true;
        break;

    case 5:
        // overhead spammer
        autoplayer_count++;
        if (autoplayer_count % AUTOP_INTERVAL == 0)
            p2->wanted_animation = overhead;
        else
            p2->wanted_animation = crouching;
        p2->is_inputting_block = true;
        break;

    case 6:
        // last strat: literally random
        p2->wanted_animation = rand() % 10;
        break;
    }
    // testing whether crMK comboes into dash_punch:
    // autoplayer_count++;
    // if (autoplayer_count % 4 == 0)
    //     p2->wanted_animation = dash_punch;
    // else
    //     p2->wanted_animation = crMK;

    // testing whether dash_punch comboes into dash_punch:
        // p2->wanted_animation = dash_punch;

    // testing whether dash_punch comboes into crLP:
    // autoplayer_count++;
    // if (autoplayer_count % 10 == 0)
    //     p2->wanted_animation = dash_punch;
    // else
    //     p2->wanted_animation = crLP;

        
}

