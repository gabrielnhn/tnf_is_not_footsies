#include "sounds.h"

void sound_setup()
{
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");
}

char *sound_enum_to_file(enum sound a)
// get the folder of sprites for a given animation
{
    switch (a)
    {
    case block:
        return "sounds/Block.wav";
    case fall_sound:
        return "sounds/Fall.wav";

    case fight:
        return "sounds/Fight!.wav";

    case final_round:
        return "sounds/FinalRound.wav";

    case good:
        return "sounds/GoodEffect.wav";

    case hard_hit:
        return "sounds/HardHit.wav";

    case KO:
        return "sounds/KO.wav";

    case light_hit:
        return "sounds/LightHit.wav";

    case medium_hit:
        return "sounds/MediumHit.wav";

    case options:
        return "sounds/Options.wav";

    case round1:
        return "sounds/Round1.wav";

    case round2:
        return "sounds/Round2.wav";

    case versus:
        return "sounds/Versus.wav";

    case warning:
        return "sounds/WarningSound.wav";

    case you_lose:
        return "sounds/YouLose.wav";

    case you_win:
        return "sounds/YouWin.wav";

    default:
        fprintf(stderr, "No such sound %d\n", a);
        exit(1);
    }
}

// ALLEGRO_SAMPLE* elephant = al_load_sample("elephant.wav");

ALLEGRO_SAMPLE **load_sounds()
// get all the sprites from the drive
{
    sound_setup();

    // store them all in an array of ALLEGRO_SAMPLE*
    ALLEGRO_SAMPLE **sounds = malloc(sizeof(ALLEGRO_SAMPLE*) * SOUNDS_N);
    must_init(sounds, "sounds array");

    char const* path; // store the path of each sprite

    for (int i = 0; i < SOUNDS_N; i++)
    // for each sound
    {
        path = sound_enum_to_file(i);
        sounds[i] = al_load_sample(path);
    }
    return sounds;
}

void destroy_sounds(ALLEGRO_SAMPLE ** sounds)
{
   for (int i = 0; i < SOUNDS_N; i++)
    // for each sound
    {
        al_destroy_sample(sounds[i]);
    } 
    free(sounds);
}


void play_sound(ALLEGRO_SAMPLE ** sounds, enum sound s)
{
    al_play_sample(
    sounds[s],              // the sample to play
    1.0,                   // gain ('volume')
    0.0,                   // pan ('balance')
    1.0,                   // speed
    ALLEGRO_PLAYMODE_ONCE, // play mode
    NULL                   // sample id
    );

}