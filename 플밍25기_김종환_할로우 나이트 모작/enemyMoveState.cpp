#include "stdafx.h"
#include "enemyMoveState.h"

enemyMoveState* enemyMoveState::instance;


enemyMoveState* enemyMoveState::getInstance()
{
    if (instance == nullptr)
    {
        instance = new enemyMoveState();
    }

    return instance;
}

void enemyMoveState::idle(enemy* cEnemy)
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
    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_idle"));
        cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_idle"));  
    }
    setEnemyState(cEnemy, enemyIdleState::getInstance());
}

void enemyMoveState::move(enemy* cEnemy)
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
        cEnemy->setEnemyPoint(PointMake(cEnemy->getEnemy().x + cosf(cEnemy->getEnemy().angle) * cEnemy->getEnemy().speedX,
            cEnemy->getEnemy().y + (-sinf(cEnemy->getEnemy().angle)) * cEnemy->getEnemy().speedY));
        cEnemy->getEnemy().curPlayAni->resume();
        //cEnemy->getEnemy().curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
    }
    else if (cEnemy->getEnemy().enemyType == XERO)
    {
        cEnemy->setEnemyImage(IMAGEMANAGER->findImage("xero_idle"));
        cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("xero_idle"));
        cEnemy->setEnemyPoint(PointMake(cEnemy->getEnemy().x + cosf(cEnemy->getEnemy().angle) * cEnemy->getEnemy().speedX,
            cEnemy->getEnemy().y + (-sinf(cEnemy->getEnemy().angle)) * cEnemy->getEnemy().speedY));
        cEnemy->getEnemy().curPlayAni->resume();
        //cEnemy->getEnemy().curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
    }
}

void enemyMoveState::attack(enemy* cEnemy)
{
    if (cEnemy->getEnemy().enemyType == ASPID)
    {
        if (cEnemy->getEnemy().dirType == LEFT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_attack_left"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_attack_left"));
            ANIMATIONMANAGER->findAnimation("aspid_attack_left")->resume();
        }
        else if (cEnemy->getEnemy().dirType == RIGHT)
        {
            cEnemy->setEnemyImage(IMAGEMANAGER->findImage("aspid_attack_right"));
            cEnemy->setEnemyAnimation(ANIMATIONMANAGER->findAnimation("aspid_attack_right"));
            ANIMATIONMANAGER->findAnimation("aspid_attack_right")->resume();
        }
        cEnemy->setEnemyAtkType(NORMAL_ATTACK);
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

void enemyMoveState::dead(enemy* cEnemy)
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
