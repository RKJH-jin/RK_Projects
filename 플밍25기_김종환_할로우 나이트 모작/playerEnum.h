#pragma once

namespace PLAYER
{
    enum DIRECTION
    {
        LEFT,
        RIGHT
    };

    enum POSITION
    {
        ONTHEGROUND,
        INTHEAIR,
        HANGING
    };

    enum STATE
    {
        IDLE_NORMAL,
        IDLE_SPECIAL,
        RUN,
        HANG,
        EVADE,
        HIT
    };

    enum STATE_JUMP
    {
        NON_JUMP,
        JUMP,
        WALL_JUMP,
        LAND,
    };

    enum STATE_ATTACK
    {
        NON_ATTACK,
        NORMAL_ATTACK,
        FLOURISH,
        THROW,
        DASH_AIR,
        DASH_GROUND,
        SPLASH_AIR,
        SPLASH_GROUND
    };
    ////////////////////////////////////

    enum END
    {
        BACK_END,
        FRONT_END
    };
}

