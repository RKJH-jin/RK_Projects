#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

void player::playerControl()
{
    // 피격 시 키 안먹힘
    if (_player.stateType != HIT)
    {
        // 벽 점프 중일 때는 못 움직임
        if (_player.jumpType != WALL_JUMP)
        {
            // 돌진/스플래쉬/창던지기 중에는 못 움직임
            if (_player.atkType == NON_ATTACK || _player.atkType == NORMAL_ATTACK)
            {
                //================왼쪽 방향키 누르고 있는 경우================//
                // 오른쪽으로 평타 중에는 왼쪽으로 못 움직임
                if (!(_player.dirType == RIGHT && _player.atkType == NORMAL_ATTACK))
                {
                    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
                    {
                        // 땅 위에서 달리기 시작할 경우
                        if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // 땅 위에서 달리는 중일 경우
                        else if (_player.posType == ONTHEGROUND && _player.stateType == RUN && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // 공중에서 움직이기 시작하는 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // 공중에서 움직이는 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // 낙하시 움직이기 시작 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // 낙하시 움직이는 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // 매달려야 하는 경우
                        else if (pixelCheckLeft() && _player.posType == INTHEAIR &&
                            _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = LEFT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // 매달리고 있고 벽 쪽으로 움직이는 경우
                        else if (pixelCheckLeft() && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // 매달리고 있고 벽 반대쪽으로 움직이는 경우
                        else if (pixelCheckRight() && _player.dirType == RIGHT && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = LEFT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                            _player.preDirType = RIGHT;
                            _player.prePosType = HANGING;
                            _player.preStateType = HANG;
                            _player.preJumpType = NON_JUMP;
                            _player.preX = _player.x;
                            _player.preY = _player.y;
                        }
                        // 벽 점프 이후 움직일 경우
                        else if (_player.posType == INTHEAIR && _player.preJumpType == WALL_JUMP)
                        {
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                    }
                }
                // 왼쪽으로 평타 중에는 오른쪽으로 못 움직임
                if (!(_player.dirType == LEFT && _player.atkType == NORMAL_ATTACK))
                {
                    //================오른쪽 방향키 누르고 있는 경우================//
                    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
                    {
                        // 땅 위에서 달리기 시작할 경우
                        if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // 땅 위에서 달리는 중일 경우
                        else if (_player.posType == ONTHEGROUND && _player.stateType == RUN && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = ONTHEGROUND;
                            _player.stateType = RUN;
                            _player.jumpType = NON_JUMP;
                        }
                        // 공중에서 움직이기 시작하는 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // 공중에서 움직이는 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                        // 낙하시 움직이기 시작 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // 낙하시 움직이는 경우
                        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                        }
                        // 매달려야 하는 경우
                        else if (pixelCheckRight() && _player.posType == INTHEAIR &&
                            _player.stateType == RUN && _player.jumpType == LAND)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // 매달리고 있고 벽 쪽으로 움직이는 경우
                        else if (pixelCheckRight() && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = HANGING;
                            _player.stateType = HANG;
                            _player.jumpType = NON_JUMP;
                        }
                        // 매달리고 있고 벽 반대쪽으로 움직이는 경우
                        else if (pixelCheckLeft() && _player.dirType == LEFT && _player.posType == HANGING &&
                            _player.stateType == HANG && _player.jumpType == NON_JUMP)
                        {
                            _player.dirType = RIGHT;
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = LAND;
                            _player.preDirType = LEFT;
                            _player.prePosType = HANGING;
                            _player.preStateType = HANG;
                            _player.preJumpType = NON_JUMP;
                            _player.preX = _player.x;
                            _player.preY = _player.y;
                        }
                        // 벽 점프 이후 움직일 경우
                        else if (_player.posType == INTHEAIR && _player.preJumpType == WALL_JUMP)
                        {
                            _player.posType = INTHEAIR;
                            _player.stateType = RUN;
                            _player.jumpType = JUMP;
                        }
                    }
                }
            }

        }

        // 돌진/스플래쉬/창던지기 중에는 못 움직임
        if (_player.atkType == NON_ATTACK || _player.atkType == NORMAL_ATTACK)
        {
            if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
            {
                // 땅에서 달리다가 땔 경우
                if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
                    _player.stateType == RUN && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = LEFT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                }
                // 공중에서 달리다가 땔 경우
                else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == JUMP)
                {
                    _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = JUMP;
                }
                // 낙하 중 달리다가 땔 경우
                else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == LAND)
                {
                    _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }
                // 어느 방향이든 매달리고 있다가 때면
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = LEFT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                }
            }

            if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
            {
                // 땅에서 달리다가 땔 경우
                if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
                    _player.stateType == RUN && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = RIGHT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                }
                // 공중에서 달리다가 땔 경우
                else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == JUMP)
                {
                    _player.dirType = RIGHT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = JUMP;
                }
                // 낙하 중 달리다가 땔 경우
                else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                    _player.stateType == RUN && _player.jumpType == LAND)
                {
                    _player.dirType = RIGHT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }
                // 어느 방향이든 매달리고 있다가 때면
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    _player.dirType = RIGHT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                }
            }
            if (!(_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP))
            {
                if (KEYMANAGER->isStayKeyDown('C'))
                {
                    // 땅에서 제자리 점프할 경우
                    if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP
                        && (_player.jumpTimer < _player.jumpTimeLimit) && _player.jumpCount == 0)
                    {
                        _player.posType = INTHEAIR;
                        _player.stateType = IDLE_NORMAL;
                        _player.jumpType = JUMP;
                    }
                    // 땅에서 달리기 점프할 경우
                    else if (_player.posType == ONTHEGROUND && _player.stateType == RUN && _player.jumpType == NON_JUMP
                        && (_player.jumpTimer < _player.jumpTimeLimit) && _player.jumpCount == 0)
                    {
                        _player.posType = INTHEAIR;
                        _player.stateType = RUN;
                        _player.jumpType = JUMP;
                    }
                }
            }

            // 벽 점프
            if (KEYMANAGER->isOnceKeyDown('C'))
            {
                if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    _player.jumpTimer += TIMEMANAGER->getElapsedTime();
                    _player.preDirType = _player.dirType;
                    if (_player.dirType == LEFT) _player.dirType = RIGHT;
                    else if (_player.dirType == RIGHT) _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = WALL_JUMP;
                    _player.preJumpType = WALL_JUMP;
                    _player.preX = _player.x;
                    _player.preY = _player.y;
                }
                // 키 조합 - 벽에서 반대방향으로 방향키 + 점프할 때
                else if (!(GetAsyncKeyState(VK_LEFT) & 0x8001) &&
                    _player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND &&
                    _player.prePosType == HANGING && _player.preStateType == HANG && _player.preJumpType == NON_JUMP &&
                    fabs(_player.preX - _player.x) < 40)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = WALL_JUMP;
                }
                else if (!(GetAsyncKeyState(VK_RIGHT) & 0x8001) &&
                    _player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND &&
                    _player.prePosType == HANGING && _player.preStateType == HANG && _player.preJumpType == NON_JUMP &&
                    fabs(_player.preX - _player.x) < 40)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = WALL_JUMP;
                }
            }

            //===================점프키 땐 경우===================//
            if (KEYMANAGER->isOnceKeyUp('C') || (_player.jumpTimer >= _player.jumpTimeLimit))
            {
                // 땅에서 제자리 점프한 경우
                if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }
                // 땅에서 달리기 점프한 경우
                else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == JUMP)
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = LAND;
                }
            }
        }

        //=========================== 공격 키 모음 ===========================//
        // 평타는 공격 애니메이션이 끝났을 때만!
        if (_player.atkType == NON_ATTACK && _player.curPlayAtkAni != nullptr && !_player.curPlayAtkAni->isPlay())
        {
            // 평타
            if (KEYMANAGER->isOnceKeyDown('X'))
            {
                //벽에 매달려서는 평타X
                if (!(_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP))
                {
                    _player.atkType = NORMAL_ATTACK;
                    _player.attackX = _player.x;
                    _player.attackY = _player.y;
                    if (_player.dirType == LEFT)
                    {
                        ANIMATIONMANAGER->resetCurrentAni("hornet_attack_left");
                    }
                    else if (_player.dirType == RIGHT)
                    {
                        ANIMATIONMANAGER->resetCurrentAni("hornet_attack_right");
                    }
                }
            }
            if (KEYMANAGER->isOnceKeyUp('X'))
            {

            }
        }

        // 특수 공격 중 다른 공격 불가
        if ((_player.atkType != DASH_GROUND && _player.atkType != DASH_AIR &&
            _player.atkType != SPLASH_GROUND && _player.atkType != SPLASH_AIR &&
            _player.atkType != THROW) &&
            !_player.curPlayAtkAni->isPlay())
        {
            _player.groundDashCount = 0;
            // 대쉬
            if (KEYMANAGER->isOnceKeyDown('Z'))
            {
                // 땅에서 대쉬
                if (_player.posType == ONTHEGROUND && _player.groundDashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;

                    else if (_player.dirType == RIGHT)
                    {
                        _player.dirType = RIGHT;
                        
                    }
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = DASH_GROUND;
                    _player.dashX = _player.x;
                    _player.dashY = _player.y;
                    _player.groundDashCount += 1;
                }
                // 공중에서 대쉬
                else if (_player.posType == INTHEAIR && _player.airDashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                    _player.atkType = DASH_AIR;
                    _player.dashX = _player.x;
                    _player.dashY = _player.y;
                    _player.airDashCount += 1;
                }
                // 매달렸을 때 대쉬
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    if (_player.dirType == LEFT) _player.dirType = RIGHT;
                    else if (_player.dirType == RIGHT) _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = DASH_AIR;
                    _player.dashX = _player.x;
                    _player.dashY = _player.y;
                    _player.airDashCount += 1;
                }
            }
            if (KEYMANAGER->isOnceKeyUp('Z'))
            {

            }
            //===============================================//
            // 창던지기
            if (KEYMANAGER->isOnceKeyDown('A'))
            {
                // 땅에서만 던질 수 있음
                if (_player.posType == ONTHEGROUND)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = THROW;
                    _player.throwX = _player.x;
                    _player.throwY = _player.y;
                    
                }
            }
            if (KEYMANAGER->isOnceKeyUp('A'))
            {

            }
            //===============================================//
            // 스플래쉬
            if (KEYMANAGER->isOnceKeyDown('S'))
            {
                _player.groundSplashCount = 0;

                // 땅에서 스플래쉬
                if (_player.posType == ONTHEGROUND && _player.groundSplashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = SPLASH_GROUND;
                    _player.splashX = _player.x;
                    _player.splashY = _player.y;
                    _player.groundSplashCount += 1;
                }
                // 공중에서 스플래쉬
                else if (_player.posType == INTHEAIR && _player.airSplashCount == 0)
                {
                    if (_player.dirType == LEFT) _player.dirType = LEFT;
                    else if (_player.dirType == RIGHT) _player.dirType = RIGHT;
                    _player.stateType = IDLE_NORMAL;
                    _player.atkType = SPLASH_AIR;
                    _player.splashX = _player.x;
                    _player.splashY = _player.y;
                    _player.airSplashCount += 1;
                }
                // 매달렸을 때 스플래쉬
                else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
                {
                    if (_player.dirType == LEFT) _player.dirType = RIGHT;
                    else if (_player.dirType == RIGHT) _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                    _player.atkType = SPLASH_AIR;
                    _player.splashX = _player.x;
                    _player.splashY = _player.y;
                }
            }
            if (KEYMANAGER->isOnceKeyUp('S'))
            {

            }
            //===============================================//
        }
    }

    //================점프 타이머 증가================//
    if ((!(!(GetAsyncKeyState('C') & 0x8000)) || _player.jumpType == JUMP) && (_player.jumpTimer < _player.jumpTimeLimit))
    {
        _player.jumpTimer += TIMEMANAGER->getElapsedTime();
        _player.jumpType = JUMP;

    }
}

