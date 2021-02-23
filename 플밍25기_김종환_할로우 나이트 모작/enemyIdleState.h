#pragma once
#include "enemyState.h"
#include "enemyMoveState.h"
#include "enemyAttackState.h"
#include "enemyDeadState.h"

class enemyIdleState : public enemyState
{
private:
    static enemyIdleState* instance;
public:
    static enemyIdleState* getInstance();

    virtual void idle(enemy* cEnemy);
    virtual void move(enemy* cEnemy);
    virtual void attack(enemy* cEnemy);
    virtual void dead(enemy* cEnemy);
};

