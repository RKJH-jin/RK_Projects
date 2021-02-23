#pragma once

using namespace PLAYER;

struct tagPlayer
{
    RECT rc;
    image* img;

    DIRECTION dirType;
    DIRECTION preDirType;

    POSITION posType;
    POSITION prePosType;

    STATE stateType;
    STATE preStateType;

    STATE_JUMP jumpType;
    STATE_JUMP preJumpType;

    STATE_ATTACK atkType;

    animation* curPlayAtkAni;

    animation* prePlayAni;
    animation* curPlayAni;


    bool isJump;
    bool isAttack;
    bool isSkill;

    float x, y;
    float width, height;
    float preX, preY;
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
    float speed;

    int maxHp;
    int hp;
    bool isDead;


    int airDashCount;
    int groundDashCount;
    int airSplashCount;
    int groundSplashCount;

    RECT atkRc;
    RECT dashRc;
    float dashRcX, dashRcY;
    float dashRcWidth, dashRcHeight;
    RECT splashRc;
    float splashRcWidth, splashRcHeight;
};