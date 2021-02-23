#pragma once
#include "enemy.h"


class enemyState
{
private:
public:
    virtual void idle(enemy* cEnemy);
    virtual void move(enemy* cEnemy);
    virtual void attack(enemy* cEnemy);
    virtual void dead(enemy* cEnemy);

protected:
    void setEnemyState(enemy* cEnemy, enemyState* state)
    {
        cEnemy->setState(state);
    }
};

