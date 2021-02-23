#include "stdafx.h"
#include "enemyIdleState.h"

enemyIdleState* enemyIdleState::instance;


enemyIdleState* enemyIdleState::getInstance()
{
    if (instance == nullptr)
    {
        instance = new enemyIdleState();
    }

    return instance;
}

void enemyIdleState::idle(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {
        if (cEnemy->getEnemy().dirType == LEFT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_move_left"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_move_left"));
        }
        else if (cEnemy->getEnemy().dirType == RIGHT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_move_right"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_move_right"));
        }
        cEnemy->getEnemy().curPlayAni->resume();
    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_idle"));
        cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_idle"));
        cEnemy->getEnemy().curPlayAni->resume();
    }
}

void enemyIdleState::move(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {
        if (cEnemy->getEnemy().dirType == LEFT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_move_left"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_move_left"));
        }
        else if (cEnemy->getEnemy().dirType == RIGHT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_move_right"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_move_right"));
        }
        cEnemy->getEnemy().curPlayAni->resume();
    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {

    }
    setEnemyState(cEnemy, enemyMoveState::getInstance());
}

void enemyIdleState::attack(enemy* cEnemy)
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
        cEnemy->setEnemyAtkType(NORMAL_ATTACK);
        cEnemy->getEnemy().curPlayAni->resume();
    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_attack"));
        cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_attack_1"));
        cEnemy->getEnemy().curPlayAni->resume();
        cEnemy->setEnemyAtkType(NORMAL_ATTACK);
        cEnemy->setEnemyWidth(370);
        cEnemy->setEnemyHeight(300);
    }
    
    setEnemyState(cEnemy, enemyAttackState::getInstance());
}

void enemyIdleState::dead(enemy* cEnemy)
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
