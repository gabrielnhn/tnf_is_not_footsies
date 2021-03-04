    
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
    
ALLEGRO_AUDIO_STREAM* play_music(const char* str)
{

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(16);


    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream(str, 2, 2048);
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);

    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());

    return music;
}

void destroy_music(ALLEGRO_AUDIO_STREAM* music)
{
    al_destroy_audio_stream(music);
}