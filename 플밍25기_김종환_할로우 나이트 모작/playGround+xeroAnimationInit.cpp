#include "stdafx.h"
#include "playGround.h"

void playGround::xeroAnimationInit()
{
    ANIMATIONMANAGER->addAnimation("xero_idle", "xero_idle", false, true, 1);
    ANIMATIONMANAGER->addAnimation("xero_attack", "xero_attack_1", 0, 2, false, false, 1);
    ANIMATIONMANAGER->addAnimation("xero_attack", "xero_attack_2", 3, 5, false, true, 1);
    ANIMATIONMANAGER->addAnimation("xero_attack", "xero_dead", 3, 5, false, false, 1);
}