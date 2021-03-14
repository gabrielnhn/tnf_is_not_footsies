#ifndef SOUNDS_H
#define SOUNDS_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <dirent.h> 
#include "utils.h"

enum sound
{
    block, fall_sound, fight, final_round, good, 
    KO, light_hit, medium_hit, round1, round2 
};
#define SOUNDS_N 10

void sound_setup();

char *sound_enum_to_file(enum sound a);

ALLEGRO_SAMPLE** load_sounds();

void destroy_sounds(ALLEGRO_SAMPLE ** sounds);

void play_sound(ALLEGRO_SAMPLE ** sounds, enum sound s);

#endif