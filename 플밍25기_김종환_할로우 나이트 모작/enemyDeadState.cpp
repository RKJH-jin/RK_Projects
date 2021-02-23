#include "stdafx.h"
#include "enemyDeadState.h"

enemyDeadState* enemyDeadState::instance;

enemyDeadState* enemyDeadState::getInstance()
{
    if (instance == nullptr)
    {
        instance = new enemyDeadState();
    }

    return instance;
}

void enemyDeadState::idle(enemy* cEnemy)
{

}

void enemyDeadState::move(enemy* cEnemy)
{

}

void enemyDeadState::attack(enemy* cEnemy)
{

}

void enemyDeadState::dead(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {
        if (!cEnemy->getEnemy().curPlayAni->isPlay())
        {
            cEnemy->setEnemyIsDead(true);
            ANIMATIONMANAGER->findAnimation("aspid_death_left")->stop();
            ANIMATIONMANAGER->findAnimation("aspid_death_right")->stop();
        }
    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        if (!cEnemy->getEnemy().curPlayAni->isPlay() && cEnemy->getEnemy().deadAniCount < 5)
        {
            cEnemy->getEnemy().curPlayAni->stop();
            cEnemy->setEnemyDeadAniCount(cEnemy->getEnemy().deadAniCount + 1);
            cEnemy->getEnemy().curPlayAni->resume();
            cEnemy->getEnemy().curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
        }
        else if (!cEnemy->getEnemy().curPlayAni->isPlay() && cEnemy->getEnemy().deadAniCount >= 5)
        {
            cEnemy->setEnemyIsDead(true);
            cEnemy->getEnemy().curPlayAni->stop();
        }
    }
    setEnemyState(cEnemy, enemyDeadState::getInstance());
}
