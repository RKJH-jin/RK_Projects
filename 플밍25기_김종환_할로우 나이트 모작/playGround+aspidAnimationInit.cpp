#include "stdafx.h"
#include "playGround.h"

void playGround::aspidAnimationInit()
{
    ANIMATIONMANAGER->addAnimation("aspid_turn_left", "aspid_turn_left", false, false, 1);
    ANIMATIONMANAGER->addAnimation("aspid_turn_right", "aspid_turn_right", true, false, 1);

    ANIMATIONMANAGER->addAnimation("aspid_move_left", "aspid_move_left", false, true, 1);
    ANIMATIONMANAGER->addAnimation("aspid_move_right", "aspid_move_right", true, true, 1);

    ANIMATIONMANAGER->addAnimation("aspid_attack_left", "aspid_attack_left", false, false, 1);
    ANIMATIONMANAGER->addAnimation("aspid_attack_right", "aspid_attack_right", true, false, 1);

    ANIMATIONMANAGER->addAnimation("aspid_death_left", "aspid_death_left", false, false, 1);
    ANIMATIONMANAGER->addAnimation("aspid_death_right", "aspid_death_right", true, false, 1);
}



