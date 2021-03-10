#ifndef MUSIC_H
#define MUSIC_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "utils.h"

ALLEGRO_AUDIO_STREAM* play_music(const char* str);
void destroy_music(ALLEGRO_AUDIO_STREAM* music);

#endif