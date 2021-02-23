#include "stdafx.h"
#include "enemyAttackState.h"

enemyAttackState* enemyAttackState::instance;


enemyAttackState* enemyAttackState::getInstance()
{
    if (instance == nullptr)
    {
        instance = new enemyAttackState();
    }

    return instance;
}

void enemyAttackState::idle(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {

    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        cEnemy->setEnemyWidth(200);
        cEnemy->setEnemyHeight(320);
    }
    
    cEnemy->setEnemyAtkType(NON_ATTACK);
    setEnemyState(cEnemy, enemyIdleState::getInstance());
}

void enemyAttackState::move(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {

    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        cEnemy->setEnemyWidth(200);
        cEnemy->setEnemyHeight(320);
    }
    cEnemy->setEnemyAtkType(NON_ATTACK);
    setEnemyState(cEnemy, enemyMoveState::getInstance());
}

void enemyAttackState::attack(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {
        if (cEnemy->getEnemy().dirType == LEFT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_attack_left"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_attack_left"));
        }
        else if (cEnemy->getEnemy().dirType == RIGHT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_attack_right"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_attack_right"));
        }
        cEnemy->getEnemy().curPlayAni->resume();
        //cEnemy->getEnemy().curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        if (cEnemy->getEnemy().curPlayAni == ANIMATIONMANAGER->findAnimation("xero_attack_1") && !cEnemy->getEnemy().curPlayAni->isPlay())
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_attack"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_attack_2"));
            ANIMATIONMANAGER->findAnimation("xero_attack_1")->stop();
        }
        else if (cEnemy->getEnemy().curPlayAni == ANIMATIONMANAGER->findAnimation("xero_attack_2"))
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_attack"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_attack_2"));
        }
        else
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_attack"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_attack_1"));
        }

        cEnemy->getEnemy().curPlayAni->resume();
        //cEnemy->getEnemy().curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
    }
}

void enemyAttackState::dead(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {
        if (cEnemy->getEnemy().dirType == LEFT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_death_left"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_death_left"));
            ANIMATIONMANAGER->findAnimation("aspid_death_left")->resume();
        }
        else if (cEnemy->getEnemy().dirType == RIGHT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_death_right"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_death_right"));
            ANIMATIONMANAGER->findAnimation("aspid_death_right")->resume();
        }

    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_attack"));
        cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_dead"));
        ANIMATIONMANAGER->findAnimation("xero_dead")->resume();
    }

    setEnemyState(cEnemy, enemyDeadState::getInstance());
}
