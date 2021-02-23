#pragma once
#include "enemyState.h"
#include "enemyIdleState.h"
#include "enemyAttackState.h"
#include "enemyDeadState.h"

class enemyMoveState : public enemyState
{
private:
    static enemyMoveState* instance;
public:
    static enemyMoveState* getInstance();

    virtual void idle(enemy* cEnemy);
    virtual void move(enemy* cEnemy);
    virtual void attack(enemy* cEnemy);
    virtual void dead(enemy* cEnemy);
};

