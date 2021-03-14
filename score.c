#include "score.h"

void check_for_highscore(int level, int frames)
// write to "highscore.txt" if $frames < highscore for a given $level
{
    FILE* h_file;
    h_file =  fopen("highscore.txt", "r"); // open hi-score file

    if (h_file == NULL) // hi-score file doesnt exist
    {
        // write the basic highscore file
        h_file = fopen("highscore.txt", "w");
        must_init(h_file, "highscore file");

        for(int i = 1; i <= LEVELS_N; i++)
        {
            if (i == level)
                fprintf(h_file, "CPU%d: %d\n", level, frames/60);
            else
                fprintf(h_file, "CPU%d: -1\n", i);
        }
        fclose(h_file);
    }
    else // hi-score file exists
    {
        fseek (h_file, 0, SEEK_END);
        int file_length = ftell (h_file); // determine its length so we can store it in a buffer
        fseek (h_file, 0, SEEK_SET); 
        
        char* buffer = malloc ((file_length + EXTRA_MEMORY) * sizeof(char));
        must_init(buffer, "file buffer");
        strcpy(buffer, "");

        char aux_str[STR_MAX];
        // now, let's write the other lines exactly as it is in the file,
        // but not the line $level if we need to rewrite it

        int j, level_hiscore;
        for (int i = 1; i <= LEVELS_N; i++) // for each line 
        {
            fscanf(h_file, "CPU%d: %d\n", &j, &level_hiscore);
            if (i != j)
            {
                perror("Hi-score file corrupted!");
                abort();
            }
            if ((i == level) && (level_hiscore == -1 || frames/60 < level_hiscore))
            // its the line we want to change AND we got a better score to replace
            {
                sprintf(aux_str, "CPU%d: %d\n", level, frames/60);
            }
            else // keep it the same
                sprintf(aux_str, "CPU%d: %d\n", i, level_hiscore);

            strcat(buffer, aux_str); // store it in the buffer
        }
        fclose (h_file); // stop reading
        // replace it:
        h_file = fopen("highscore.txt", "w");
        fputs(buffer, h_file);
        fclose(h_file);
    }
}

void get_highscores(int* array)
// get the highscores from "highscores.txt" and store them in a given array
{
    FILE* h_file;
    h_file =  fopen("highscore.txt", "r"); // open hi-score file

    if (h_file == NULL) // hi-score file doesnt exist
    {
        for(int i = 0; i < LEVELS_N; i++)
        {
            array[i] = -1; // no values for any level!
        }
    }
    else
    {
        int j;
        for (int i = 1; i <= LEVELS_N; i++) // for each line 
        {
            fscanf(h_file, "CPU%d: %d\n", &j, &array[i-1]);
            if (i != j)
            {
                perror("Hi-score file corrupted!");
                abort();
            }
        }
    }
}