#pragma once

namespace ENEMY
{
    enum ENEMYTYPE
    {
        ASPID,
        XERO
    };

    enum DIRECTIONTYPE
    {
        LEFT,
        RIGHT
    };

    enum POSTIONTYPE
    {
        ONTHEGROUND,
        INTHEAIR,
        HANGING
    };

    enum STATETYPE
    {
        IDLE,
        MOVE
    };

    enum JUMPTYPE
    {
        NON_JUMP,
        JUMP,
        LAND
    };

    enum ATTACKTYPE
    {
        NON_ATTACK,
        NORMAL_ATTACK,
        SPECIAL_ATTACK
    };

    enum PHASE
    {
        PHASE_1,
        PHASE_2,
        PHASE_3,
        PHASE_4
    };
}

