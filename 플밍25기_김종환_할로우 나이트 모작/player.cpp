#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"
#include "enemyManager.h"


player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
    makePlayerHornet();

    return S_OK;
}

void player::release()
{
   
}

void player::update()
{
    // 좌우 중복키 처리
    if ((GetAsyncKeyState(VK_LEFT) & 0x8001) && (GetAsyncKeyState(VK_RIGHT) & 0x8000))
    {
        if (_player.stateType != PLAYER::HIT)
        {
            if (_player.posType == PLAYER::HANGING) _player.stateType = PLAYER::HANG;
            else if (_player.jumpType == PLAYER::WALL_JUMP)
            {
                if (_player.preDirType == PLAYER::LEFT) _player.dirType = PLAYER::LEFT;
                else if (_player.preDirType == PLAYER::RIGHT) _player.dirType = PLAYER::RIGHT;
                _player.stateType = RUN;
            }
            else
            {
                _player.stateType = IDLE_NORMAL;
                ANIMATIONMANAGER->findAnimation("hornet_run_left_1")->stop();
                ANIMATIONMANAGER->findAnimation("hornet_run_left_2")->stop();
                ANIMATIONMANAGER->findAnimation("hornet_run_right_1")->stop();
                ANIMATIONMANAGER->findAnimation("hornet_run_right_2")->stop();
            }
            //===================점프키 누른 경우===================//
            if (KEYMANAGER->isOnceKeyUp('C') || (_player.jumpTimer >= _player.jumpTimeLimit))
            {
                // 땅에서 제자리 점프한 경우
                if (_player.posType == PLAYER::INTHEAIR && _player.stateType == PLAYER::IDLE_NORMAL && _player.jumpType == PLAYER::JUMP)
                {
                    _player.posType = PLAYER::INTHEAIR;
                    _player.stateType = PLAYER::IDLE_NORMAL;
                    _player.jumpType = PLAYER::LAND;

                }
                // 땅에서 달리기 점프한 경우
                else if (_player.posType == PLAYER::INTHEAIR && _player.stateType == PLAYER::RUN && _player.jumpType == PLAYER::JUMP)
                {
                    _player.posType = PLAYER::INTHEAIR;
                    _player.stateType = PLAYER::RUN;
                    _player.jumpType = PLAYER::LAND;
                }
            }
            //================점프 타이머 증가================//
            if (!(!(GetAsyncKeyState('C') & 0x8000)) || _player.jumpType == PLAYER::JUMP)
            {
                _player.jumpTimer += TIMEMANAGER->getElapsedTime();
            }
        }
        
    }
    // 아주 가끔 아래 경우가 나타날 때도 있어서 추가
    else if ((GetAsyncKeyState(VK_RIGHT) & 0x8001) && (GetAsyncKeyState(VK_LEFT) & 0x8000)) 
    {
        if (_player.stateType != PLAYER::HIT)
        {
            if (_player.posType == PLAYER::HANGING) _player.stateType = PLAYER::HANG;
            else if (_player.jumpType == PLAYER::WALL_JUMP)
            {
                if (_player.preDirType == PLAYER::LEFT) _player.dirType = PLAYER::LEFT;
                else if (_player.preDirType == PLAYER::RIGHT) _player.dirType = PLAYER::RIGHT;
                _player.stateType = RUN;
            }
            else
            {
                _player.stateType = IDLE_NORMAL;
                ANIMATIONMANAGER->findAnimation("hornet_run_left_1")->stop();
                ANIMATIONMANAGER->findAnimation("hornet_run_left_2")->stop();
                ANIMATIONMANAGER->findAnimation("hornet_run_right_1")->stop();
                ANIMATIONMANAGER->findAnimation("hornet_run_right_2")->stop();
            }
            //===================점프키 누른 경우===================//
            if (KEYMANAGER->isOnceKeyUp('C') || (_player.jumpTimer >= _player.jumpTimeLimit))
            {
                // 땅에서 제자리 점프한 경우
                if (_player.posType == PLAYER::INTHEAIR && _player.stateType == PLAYER::IDLE_NORMAL && _player.jumpType == PLAYER::JUMP)
                {
                    _player.posType = PLAYER::INTHEAIR;
                    _player.stateType = PLAYER::IDLE_NORMAL;
                    _player.jumpType = PLAYER::LAND;
                }
                // 땅에서 달리기 점프한 경우
                else if (_player.posType == PLAYER::INTHEAIR && _player.stateType == PLAYER::RUN && _player.jumpType == PLAYER::JUMP)
                {
                    _player.posType = PLAYER::INTHEAIR;
                    _player.stateType = PLAYER::RUN;
                    _player.jumpType = PLAYER::LAND;
                }
            }
            //================점프 타이머 증가================//
            if (!(!(GetAsyncKeyState('C') & 0x8000)) || _player.jumpType == PLAYER::JUMP)
            {
                _player.jumpTimer += TIMEMANAGER->getElapsedTime();
            }
        }
        
    }
    else
    {
        playerControl();
    }
    playerAtkEnemy();
    playerMove();
    hornetAnimationSelect();
    animationUpdateReset();
}

void player::render()
{

   


    /*char str[256];
    sprintf_s(str, "점프키 눌림여부: %d", !(GetAsyncKeyState('C') & 0x8001));
    

    char str1[256];
    switch (_player.dirType)
    {
    case PLAYER::LEFT:
        sprintf_s(str1, "LEFT");
        break;
    case PLAYER::RIGHT:
        sprintf_s(str1, "RIGHT");
        break;
    }

    char str2[256];
    switch (_player.posType)
    {
    case PLAYER::ONTHEGROUND:
        sprintf_s(str2, "ONTHEGROUND");
        break;
    case PLAYER::INTHEAIR:
        sprintf_s(str2, "INTHEAIR");
        break;
    case PLAYER::HANGING:
        sprintf_s(str2, "HANGING");
        break;
    }
    
    char str3[256];
    switch (_player.stateType)
    {
    case PLAYER::IDLE_NORMAL:
        sprintf_s(str3, "IDLE_NORMAL");
        break;
    case PLAYER::IDLE_SPECIAL:
        sprintf_s(str3, "IDLE_SPECIAL");
        break;
    case PLAYER::RUN:
        sprintf_s(str3, "RUN");
        break;
    case PLAYER::HANG:
        sprintf_s(str3, "HANG");
        break;
    case PLAYER::EVADE:
        sprintf_s(str3, "EVADE");
        break;
    case PLAYER::HIT:
        sprintf_s(str3, "HIT");
        break;
    }

    char str4[256];
    switch (_player.jumpType)
    {
    case PLAYER::NON_JUMP:
        sprintf_s(str4, "NON_JUMP");
        break;
    case PLAYER::JUMP:
        sprintf_s(str4, "JUMP");
        break;
    case PLAYER::WALL_JUMP:
        sprintf_s(str4, "WALL_JUMP");
        break;
    case PLAYER::LAND:
        sprintf_s(str4, "LAND");
        break;
    }

    TextOut(getMemDC(), WINSIZEX - 500, 50, str, strlen(str));
    TextOut(getMemDC(), WINSIZEX - 500, 70, str1, strlen(str1));
    TextOut(getMemDC(), WINSIZEX - 500, 90, str2, strlen(str2));
    TextOut(getMemDC(), WINSIZEX - 500, 110, str3, strlen(str3));
    TextOut(getMemDC(), WINSIZEX - 500, 130, str4, strlen(str4));

    char str5[256];
    sprintf_s(str5, "%f", _player.jumpTimer);
    TextOut(getMemDC(), WINSIZEX - 500, 150, str5, strlen(str5));

    char str6[256];
    switch (_player.atkType)
    {
    case PLAYER::NON_ATTACK:
        sprintf_s(str6, "NON_ATTACK");
        break;
    case PLAYER::NORMAL_ATTACK:
        sprintf_s(str6, "NORMAL_ATTACK");
        break;
    case PLAYER::FLOURISH:
        sprintf_s(str6, "FLOURISH");
        break;
    case PLAYER::THROW:
        sprintf_s(str6, "THROW");
        break;
    case PLAYER::DASH_AIR:
        sprintf_s(str6, "DASH_AIR");
        break;
    case PLAYER::DASH_GROUND:
        sprintf_s(str6, "DASH_GROUND");
        break;
    case PLAYER::SPLASH_AIR:
        sprintf_s(str6, "SPLASH_AIR");
        break;
    case PLAYER::SPLASH_GROUND:
        sprintf_s(str6, "SPLASH_GROUND");
        break;
    }
    TextOut(getMemDC(), WINSIZEX - 500, 170, str6, strlen(str6));*/


    //Rectangle(getMemDC(), _player.rc);
    /*if (_player.atkType == PLAYER::DASH_GROUND || _player.atkType == PLAYER::DASH_AIR)
    {
        Rectangle(getMemDC(), _player.dashRc);
    }
    if (_player.atkType == PLAYER::SPLASH_GROUND || _player.atkType == PLAYER::SPLASH_AIR)
    {
        Rectangle(getMemDC(), _player.splashRc);
    }
    if (_player.atkType == PLAYER::NORMAL_ATTACK)
    {
        Rectangle(getMemDC(), _player.atkRc);
    }*/
   
    hornetAnimationRender();
}


void player::playerAtkEnemy()
{
    // Aspid
    for (int i = 0; i < _cEnemyManager->getVAspid().size(); ++i)
    {
        if (!_player.isAttack)
        {
            RECT atkTemp;
            if (_player.atkType == PLAYER::DASH_GROUND || _player.atkType == PLAYER::DASH_AIR)
            {
                if (IntersectRect(&atkTemp, &_player.dashRc, &_cEnemyManager->getVAspid()[i]->getEnemyRect()))
                {
                    cout << "atk3" << endl;
                    _cEnemyManager->getVAspid()[i]->hitDamage(50);
                    _player.isAttack = true;
                }
            }
            else if (_player.atkType == PLAYER::SPLASH_GROUND || _player.atkType == PLAYER::SPLASH_AIR)
            {
                if (IntersectRect(&atkTemp, &_player.splashRc, &_cEnemyManager->getVAspid()[i]->getEnemyRect()))
                {
                    cout << "atk2" << endl;
                    _cEnemyManager->getVAspid()[i]->hitDamage(50);
                    _player.isAttack = true;
                }
            }
            else if (_player.atkType == PLAYER::NORMAL_ATTACK)
            {
                if (IntersectRect(&atkTemp, &_player.atkRc, &_cEnemyManager->getVAspid()[i]->getEnemyRect()))
                {
                    cout << "atk1" << endl;
                    _cEnemyManager->getVAspid()[i]->hitDamage(50);
                    _player.isAttack = true;
                }
            }
        }
    }

    // Xero
    for (int i = 0; i < _cEnemyManager->getVXero().size(); ++i)
    {
        if (!_player.isAttack)
        {
            RECT atkTemp;
            if (_player.atkType == PLAYER::DASH_GROUND || _player.atkType == PLAYER::DASH_AIR)
            {
                if (IntersectRect(&atkTemp, &_player.dashRc, &_cEnemyManager->getVXero()[i]->getEnemyRect()))
                {
                    cout << "atk3" << endl;
                    _cEnemyManager->getVXero()[i]->hitDamage(50);
                    _player.isAttack = true;
                }
            }
            else if (_player.atkType == PLAYER::SPLASH_GROUND || _player.atkType == PLAYER::SPLASH_AIR)
            {
                if (IntersectRect(&atkTemp, &_player.splashRc, &_cEnemyManager->getVXero()[i]->getEnemyRect()))
                {
                    cout << "atk2" << endl;
                    _cEnemyManager->getVXero()[i]->hitDamage(50);
                    _player.isAttack = true;
                }
            }
            else if (_player.atkType == PLAYER::NORMAL_ATTACK)
            {
                if (IntersectRect(&atkTemp, &_player.atkRc, &_cEnemyManager->getVXero()[i]->getEnemyRect()))
                {
                    cout << "atk1" << endl;
                    _cEnemyManager->getVXero()[i]->hitDamage(50);
                    _player.isAttack = true;
                }
            }
        }
    }
}

void player::hitDamage(float dmg)
{
    _player.hp -= dmg;
}
