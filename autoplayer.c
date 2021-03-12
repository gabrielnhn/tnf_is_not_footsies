#include "autoplayer.h"

void autoplayer_setup()
{
    // setup for random values
    time_t t;
    srand((unsigned) time(&t));
}

int autoplayer_count;

void get_autoplayer_input(player* p1, player* p2)
{
    // strat1: literally random
    p2->wanted_animation = rand() % 10;

    // testing whether overhead is punishable:
    // p2->wanted_animation = overhead;
    
    return;
}

