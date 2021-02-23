#pragma once
#include "enemyEnum.h"

using namespace ENEMY;

struct tagEnemy
{
    RECT rc;
    image* img;
    RECT searchRect;

    ENEMYTYPE enemyType;

    DIRECTIONTYPE dirType;
    DIRECTIONTYPE preDirType;

    POSTIONTYPE posType;
    POSTIONTYPE prePosType;

    STATETYPE stateType;
    STATETYPE preStateType;

    JUMPTYPE jumpType;
    JUMPTYPE preJumpType;

    ATTACKTYPE atkType;
    ATTACKTYPE preAtkType;

    PHASE phase;

    animation* prePlayAtkAni;
    animation* curPlayAtkAni;

    animation* prePlayAni;
    animation* curPlayAni;


    float x, y;
    float preX, preY;
    float width, height;
    
    float attackX, attackY;
    float dashX, dashY;
    float throwX, throwY;
    float splashX, splashY;

    float jumpPower;
    float jumpTimeLimit;
    float jumpTimer;
    int jumpCount;

    float angle;
    float gravity;
    float speedX;
    float speedY;

    float hp;
    bool isDead;

    int airDashCount;
    int groundDashCount;
    int airSplashCount;
    int groundSplashCount;

    RECT dashRc;
    float dashRcX, dashRcY;
    float dashRcWidth, dashRcHeight;
    RECT splashRc;
    float splashRcWidth, splashRcHeight;

    bool phase1;
    bool phase2;
    bool phase3;
    bool isAtking;

    int deadAniCount;
};