#include "attacks.h"

bool is_attack(enum animation a)
{
    switch (a)
    {
    case crLP:
    case crMK:
    case dash_punch:
    case overhead:
        return true;
    
    default:
        return false;
    }
}