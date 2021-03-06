#include "animation.h"

char* animation_enum_to_folder(enum animation a)
// get the folder of sprites for a given animation
{
    switch (a)
    {
    case idle:
        return "animation/1-idle/";
    case walk_forward:
        return "animation/2-walk-forward/";

    case walk_backwards:
        return "animation/3-walk-backwards/";

    case dash:
        return "animation/4-dash/";

    case backdash:
        return "animation/5-backdash/";

    case crouching:
        return "animation/6-crouching/";

    case crLP:
        return "animation/7-crLP/";

    case crMK:
        return "animation/8-crMK/";

    case dash_punch:
        return "animation/9-dash-punch/";

    case overhead:
        return "animation/10-overhead/";

    case block_high:
        return "animation/11-block_high/";

    case block_low:
        return "animation/12-block_low/";

    case fall:
        return "animation/13-fall/";

    case high_hitstun:
        return "animation/14-high-hitstun/";

    case low_hitstun:
        return "animation/15-low-hitstun/";

    case rise:
        return "animation/16-rise/";

    default:
        fprintf(stderr, "No such animation %d\n", a);
        exit(1);
    }
}
