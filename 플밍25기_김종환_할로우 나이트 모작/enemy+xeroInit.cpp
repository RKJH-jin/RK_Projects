#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyIdleState.h"
#include "enemyMoveState.h"
#include "enemyAttackState.h"
#include "enemyDeadState.h"

void enemy::xeroInit(float x, float y)
{
    _enemy.enemyType = XERO;

    _state = enemyIdleState::getInstance();

    _enemy.dirType = LEFT;
    _enemy.preDirType = LEFT;

    _enemy.posType = INTHEAIR;
    _enemy.prePosType = INTHEAIR;

    _enemy.stateType = IDLE;
    _enemy.preStateType = IDLE;

    _enemy.jumpType = NON_JUMP;
    _enemy.preJumpType = NON_JUMP;

    _enemy.atkType = NON_ATTACK;
    _enemy.preAtkType = NON_ATTACK;
    
    _enemy.phase = PHASE_1;

    _enemy.img = IMAGEMANAGER->findImage("xero_idle");
    _enemy.curPlayAni = ANIMATIONMANAGER->findAnimation("xero_idle");
    _enemy.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("xero_attack_1");

    _enemy.x = x;
    _enemy.y = y;

    _enemy.width = 200;
    _enemy.height = 320;

    _enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.width, _enemy.height);

    _enemy.angle = PI;
    _enemy.speedX = 10;
    _enemy.speedY = 0;
    _enemy.hp = 500;
    _enemy.isDead = false;
    _enemy.phase1 = false;
    _enemy.phase2 = false;
    _enemy.phase3 = false;
    _enemy.isAtking = false;
    _enemy.deadAniCount = 0;
}