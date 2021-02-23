#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "projectile.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
    for (int i = 0; i < 0; ++i)
    {
        enemy* tAspid;
        tAspid = new aspid;
        tAspid->aspidInit(WINSIZEX + 300 + 400 * i, 300);
        _vAspid.push_back(tAspid);
    }   

    enemy* tXero;
    tXero = new xero;
    tXero->xeroInit(5000, 300);
    _vXero.push_back(tXero);
    
    return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
    //==========================ASPID==========================//
    for (int i = 0; i < _vAspid.size(); ++i)
    {
        tagEnemy tEnemy = _vAspid[i]->getEnemy();
        // 죽었니 살았니?
        if (tEnemy.hp <= 0)
        {
            _vAspid[i]->enemyDead();
        }
        else // 살았는디여?
        {   
            // 공격 중이니?
            if (tEnemy.atkType == ENEMY::ATTACKTYPE::NORMAL_ATTACK) // 공격 중인뎁셔?
            {
                // 공격 모션 끝났니?
                if (!tEnemy.curPlayAni->isPlay()) // ㅇㅇ...
                {
                    float tempAngle = getAngle(_vAspid[i]->getEnemy().x, _vAspid[i]->getEnemy().y, _cPlayer->getPlayer().x, _cPlayer->getPlayer().y);
                    _vAspid[i]->setEnemyAngle(tempAngle);
                    _cProjectile->aspidPJInit(tEnemy.x, tEnemy.y, tEnemy.width, tEnemy.height, tEnemy.angle, tEnemy.enemyType, tEnemy.dirType);
                    tEnemy.curPlayAni->stop();
                    _vAspid[i]->enemyIdle();
                }
                else // ㄴㄴ...
                {
                    _vAspid[i]->enemyAttack();
                }
            }
            else if (tEnemy.atkType == ENEMY::ATTACKTYPE::NON_ATTACK) // 공격 안하고 있는뎁셔?
            {
                // 어느 방향 봐야하니?
                if (_cPlayer->getPlayer().x <= _vAspid[i]->getEnemy().x) // 왼쪽!
                {
                    _vAspid[i]->setEnemyDir(ENEMY::DIRECTIONTYPE::LEFT);
                }
                else if (_vAspid[i]->getEnemy().x < _cPlayer->getPlayer().x) // 오른쪽!
                {
                    _vAspid[i]->setEnemyDir(ENEMY::DIRECTIONTYPE::RIGHT);
                }

                float tempDistance = getDistance(_cPlayer->getPlayer().x, _cPlayer->getPlayer().y, _vAspid[i]->getEnemy().x, _vAspid[i]->getEnemy().y);
                // 움직일꺼니 공격할꺼니?
                if (tempDistance < 750) // 공격!
                {
                    _vAspid[i]->enemyAttack();
                }             
                else if (750 <= tempDistance && tempDistance < 1000) // 무브!
                {
                    float tempAngle = getAngle(_vAspid[i]->getEnemy().x, _vAspid[i]->getEnemy().y, _cPlayer->getPlayer().x, _cPlayer->getPlayer().y);
                    _vAspid[i]->setEnemyAngle(tempAngle);
                    _vAspid[i]->enemyMove();
                }
                else // 대기!
                {
                    _vAspid[i]->enemyIdle();
                }
            }
        }
        // 업데이뚜...
        _vAspid[i]->update();
    }
    //================================Xero================================//
    for (int i = 0; i < _vXero.size(); ++i)
    {
        tagEnemy tEnemy = _vXero[i]->getEnemy();
        // 죽었니 살았니?
        if (tEnemy.hp <= 0)
        {
            _vXero[i]->enemyDead();
        }
        else // 살았는디여?
        {
            // phase 업데이트
            if (200 < tEnemy.hp && tEnemy.hp <= 350)
            {
                _vXero[i]->setEnemyPhase(ENEMY::PHASE_2);
            }
            else if (tEnemy.hp <= 200)
            {
                _vXero[i]->setEnemyPhase(ENEMY::PHASE_3);
            }
            // phase업데이트에 따른 창 생성
            if (tEnemy.phase == ENEMY::PHASE::PHASE_1)
            {
                if (!tEnemy.phase1)
                {
                    _cProjectile->xeroPJInit(tEnemy.x, tEnemy.y,
                        tEnemy.width, tEnemy.height,
                        tEnemy.angle,
                        ENEMY::PHASE::PHASE_1);
                    _vXero[i]->setEnemyPhase1(true);
                }
            }
            else if (tEnemy.phase == ENEMY::PHASE::PHASE_2)
            {
                if (!tEnemy.phase2)
                {
                    _cProjectile->xeroPJInit(tEnemy.x, tEnemy.y,
                        tEnemy.width, tEnemy.height,
                        tEnemy.angle,
                        ENEMY::PHASE::PHASE_2);
                    _vXero[i]->setEnemyPhase2(true);
                }
            }
            else if (tEnemy.phase == ENEMY::PHASE::PHASE_3)
            {
                if (!tEnemy.phase3)
                {
                    _cProjectile->xeroPJInit(tEnemy.x, tEnemy.y,
                        tEnemy.width, tEnemy.height,
                        tEnemy.angle,
                        ENEMY::PHASE::PHASE_3);
                    _vXero[i]->setEnemyPhase3(true);
                }
            }
            // 공격 중이니?
            if (tEnemy.atkType == ENEMY::ATTACKTYPE::NORMAL_ATTACK) // 공격 중인뎁셔?
            {
                // 공격이 끝났니?
                if (tEnemy.curPlayAni == ANIMATIONMANAGER->findAnimation("xero_attack_2") && !tEnemy.curPlayAni->isPlay()) // ㅇㅇ...
                {
                    float tempAngle = getAngle(_vXero[i]->getEnemy().x, _vXero[i]->getEnemy().y, _cPlayer->getPlayer().x, _cPlayer->getPlayer().y);
                    _vXero[i]->setEnemyAngle(tempAngle);
                   
                    tEnemy.curPlayAni->stop();
                    _vXero[i]->enemyIdle();
                }
                else // ㄴㄴ...
                {
                    _vXero[i]->enemyAttack();
                }
            }
            else if (tEnemy.atkType == ENEMY::ATTACKTYPE::NON_ATTACK) // 공격 안하고 있는뎁셔?
            {
                // 어느 방향 봐야하니?
                if (_cPlayer->getPlayer().x <= _vXero[i]->getEnemy().x) // 왼쪽!
                {
                    _vXero[i]->setEnemyDir(ENEMY::DIRECTIONTYPE::LEFT);
                }
                else if (_vXero[i]->getEnemy().x < _cPlayer->getPlayer().x) // 오른쪽!
                {
                    _vXero[i]->setEnemyDir(ENEMY::DIRECTIONTYPE::RIGHT);
                }

                float tempDistance = getDistance(_cPlayer->getPlayer().x, _cPlayer->getPlayer().y, _vXero[i]->getEnemy().x, _vXero[i]->getEnemy().y);
                // 움직일꺼니 공격할꺼니?
                if (tempDistance < 500) // 공격!
                {
                    _vXero[i]->enemyAttack();
                    
                }
                else if (500 <= tempDistance && tempDistance < 1000) // 무브!
                {
                    float tempAngle = getAngle(_vXero[i]->getEnemy().x, _vXero[i]->getEnemy().y, _cPlayer->getPlayer().x, _cPlayer->getPlayer().y);
                    _vXero[i]->setEnemyAngle(tempAngle);
                    _vXero[i]->enemyMove();
                }
                else // 대기!
                {
                    _vXero[i]->enemyIdle();
                }
            }
        }
        // 업데이뚜...
        _vXero[i]->update();
    }
    eraseEnemy();
    
}

void enemyManager::render()
{
    for (int i = 0; i < _vAspid.size(); ++i)
    {
        if (!_vAspid[i]->getEnemy().isDead)
        {
            _vAspid[i]->render();
        }
        
    }

    for (int i = 0; i < _vXero.size(); ++i)
    {
        _vXero[i]->render();
    }
}

void enemyManager::eraseEnemy()
{
    for (_viAspid = _vAspid.begin(); _viAspid != _vAspid.end();)
    {
        if ((*_viAspid)->getEnemy().isDead)
        {
            _viAspid = _vAspid.erase(_viAspid);
        }
        else ++_viAspid;
    }

    for (_viXero = _vXero.begin(); _viXero != _vXero.end();)
    {
        if ((*_viXero)->getEnemy().isDead)
        {
            _viXero = _vXero.erase(_viXero);
        }
        else ++_viXero;
    }
}


