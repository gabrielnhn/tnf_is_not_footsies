#include "utils.h"

void must_init(bool test, const char *description)
// Used to initialize modules and immediately test whether they work
{
    if(test) return;
    printf("couldn't initialize %s\n", description);
    exit(1);
}

bool inrange(int x, int min, int max)
{
    return ((min <= x) && (x <= max));
}

void bad_malloc()
{
    perror("Bad memory allocation\n");
    exit(1);
}

bool in_array(char x, unsigned char* array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == x)
            return true;
    }
    return false;
}

void print_array(unsigned char* array, int array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        printf("%d-", (int)(array[i]));
    }
    printf("\n");
}