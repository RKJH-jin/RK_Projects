#include "stdafx.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyIdleState.h"
#include "enemyMoveState.h"
#include "enemyAttackState.h"
#include "enemyDeadState.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{



    return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
    _enemy.curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
    _enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.width, _enemy.height);
}

void enemy::render()
{
    //Rectangle(getMemDC(), _enemy.rc);
    if (_enemy.enemyType == ASPID)
    {
        if (_enemy.dirType == LEFT)
        {
            _enemy.img->aniRender(getMemDC(), _enemy.rc.left - 20, _enemy.rc.top - 15, _enemy.curPlayAni);
        }
        else if (_enemy.dirType == RIGHT)
        {
            _enemy.img->aniRender(getMemDC(), _enemy.rc.left - 5, _enemy.rc.top - 15, _enemy.curPlayAni);
        }
        
    }
    else if (_enemy.enemyType == XERO)
    {
        _enemy.img->aniRender(getMemDC(), _enemy.rc.left, _enemy.rc.top, _enemy.curPlayAni);
    }
}

void enemy::enemyIdle()
{
    _state->idle(this);
}

void enemy::enemyMove()
{
    _state->move(this);
}

void enemy::enemyAttack()
{
    _state->attack(this);
}

void enemy::enemyDead()
{
    _state->dead(this);
}

void enemy::hitDamage(float dmg)
{
    _enemy.hp -= dmg;
}




