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
    return (min <= x && x <= max);
}
