#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyIdleState.h"
#include "enemyMoveState.h"
#include "enemyAttackState.h"
#include "enemyDeadState.h"

using namespace ENEMY;

void enemy::aspidInit(float x, float y)
{
    _enemy.enemyType = ASPID;

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

    _enemy.img = IMAGEMANAGER->findImage("aspid_move_left");
    _enemy.curPlayAni = ANIMATIONMANAGER->findAnimation("aspid_move_left");
    _enemy.curPlayAtkAni = ANIMATIONMANAGER->findAnimation("aspid_attack_left");

    _enemy.x = x;
    _enemy.y = y;
    
    _enemy.width = 120;
    _enemy.height = 100;

    _enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.width, _enemy.height);

    _enemy.angle = PI;
    _enemy.speedX = 5;
    _enemy.speedY = 5;
    _enemy.hp = 100;
    _enemy.isDead = false;

}





