#include "music.h"
    
ALLEGRO_AUDIO_STREAM* play_music(const char* str)
{
    must_init(al_install_audio(), "allegro audio");
    must_init(al_init_acodec_addon(), "acodec addon");
     must_init(al_reserve_samples(16), "reserve samples");

    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream(str, 2, 2048);
    must_init(music, "music");
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);

    ALLEGRO_MIXER* mixer = al_get_default_mixer();
    must_init(music, "audio mixer");
    al_attach_audio_stream_to_mixer(music, mixer);

    return music;
}

void destroy_music(ALLEGRO_AUDIO_STREAM* music)
{
    al_destroy_audio_stream(music);
}