#pragma once
#include "enemyState.h"
#include "enemyIdleState.h"
#include "enemyMoveState.h"
#include "enemyDeadState.h"

class enemyAttackState : public enemyState
{
private:
    static enemyAttackState* instance;
public:
    static enemyAttackState* getInstance();

    virtual void idle(enemy* cEnemy);
    virtual void move(enemy* cEnemy);
    virtual void attack(enemy* cEnemy);
    virtual void dead(enemy* cEnemy);
};

