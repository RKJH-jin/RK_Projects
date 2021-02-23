#pragma once
#include "enemyState.h"
#include "enemyIdleState.h"
#include "enemyMoveState.h"
#include "enemyAttackState.h"

class enemyDeadState : public enemyState
{
private:
    static enemyDeadState* instance;
public:
    static enemyDeadState* getInstance();

    virtual void idle(enemy* cEnemy);
    virtual void move(enemy* cEnemy);
    virtual void attack(enemy* cEnemy);
    virtual void dead(enemy* cEnemy);
};

