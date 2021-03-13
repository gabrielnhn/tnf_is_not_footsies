#include "autoplayer.h"

void autoplayer_setup()
{
    // setup for random values
    time_t t;
    srand((unsigned) time(&t));
}

// int autoplayer_count;

void get_autoplayer_input(player* p1, player* p2)
{
    // strat1: literally random
    p2->wanted_animation = rand() % 10;
    
    // testing whether crMK comboes into dash_punch:
    // autoplayer_count++;
    // if (autoplayer_count % 4 == 0)
    //     p2->wanted_animation = dash_punch;
    // else
    //     p2->wanted_animation = crMK;
    
    return;
}

