#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

void player::playerMove()
{
    if (_player.stateType != HIT)
    {
        //========================일반 공격 또는 그냥 이동 중일 때========================//
        if (_player.atkType == NON_ATTACK || _player.atkType == NORMAL_ATTACK)
        {
            //========================왼쪽========================//
            //========================X축========================//
            // 땅에서 달릴 때
            if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
                _player.stateType == RUN && _player.jumpType == NON_JUMP)
            {
                _player.x -= _player.speed;
                _player.width = 70;
                _player.height = 160;
            }
            // 공중에서 움직일 때
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {
                _player.x -= _player.speed;
                _player.width = 65;
                _player.height = 145;
            }
            // 낙하중에 움직일 때
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                _player.x -= _player.speed;
                _player.width = 65;
                _player.height = 145;
            }
            //========================Y축========================//
            // 제자리 점프했을 때
            if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
            {

                _player.y -= _player.jumpPower;
                _player.width = 65;
                _player.height = 145;

            }
            // 달리기 점프했을 때
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {

                _player.y -= _player.jumpPower;
                _player.width = 65;
                _player.height = 145;

            }
            // 제자리 낙하 중일 때
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
            {
                _player.y += _player.gravity;
                _player.jumpTimer = _player.jumpTimeLimit;
                _player.width = 65;
                _player.height = 145;
            }
            // 달리기 낙하 중일 때
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                _player.y += _player.gravity;
                _player.jumpTimer = _player.jumpTimeLimit;
                _player.width = 65;
                _player.height = 145;
            }
            // 벽에 매달려서 가만히 있을 때
            else if (_player.dirType == LEFT && _player.posType == HANGING &&
                _player.stateType == HANG && _player.jumpType == NON_JUMP)
            {
                _player.y += _player.gravity / 2;
                _player.width = 75;
                _player.height = 170;
            }
            //========================벽점프========================//
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == WALL_JUMP)
            {
                _player.x += _player.speed;
                _player.y -= _player.gravity;
                _player.width = 65;
                _player.height = 145;
                if (fabs(_player.preX - _player.x) >= 70)
                {
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = JUMP;
                    _player.jumpTimer = _player.jumpTimeLimit / 2;
                }
            }

            //========================오른쪽========================//
            //========================X축========================//
            // 땅에서 달릴 때
            if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
                _player.stateType == RUN && _player.jumpType == NON_JUMP)
            {
                _player.x += _player.speed;
                _player.width = 70;
                _player.height = 160;
            }
            // 공중에서 움직일 때
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {
                _player.x += _player.speed;
                _player.width = 65;
                _player.height = 145;
            }
            // 공중에서 움직일 때
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                _player.x += _player.speed;
                _player.width = 65;
                _player.height = 145;
            }
            //========================Y축========================//
            // 제자리 점프했을 때
            if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == JUMP)
            {
                _player.y -= _player.jumpPower;
                _player.width = 65;
                _player.height = 145;
            }
            // 달리기 점프했을 때
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == JUMP)
            {
                _player.y -= _player.jumpPower;
                _player.width = 65;
                _player.height = 145;
            }
            // 제자리 낙하 중일 때
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
            {
                _player.y += _player.gravity;
                _player.jumpTimer = _player.jumpTimeLimit;
                _player.width = 65;
                _player.height = 145;
            }
            // 달리기 낙하 중일 때
            else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == LAND)
            {
                _player.y += _player.gravity;
                _player.jumpTimer = _player.jumpTimeLimit;
                _player.width = 65;
                _player.height = 145;
            }
            // 벽에 매달려서 가만히 있을 때
            else if (_player.dirType == RIGHT && _player.posType == HANGING &&
                _player.stateType == HANG && _player.jumpType == NON_JUMP)
            {
                _player.y += _player.gravity / 2;
                _player.width = 75;
                _player.height = 170;
            }
            //========================벽점프========================//
            else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
                _player.stateType == RUN && _player.jumpType == WALL_JUMP)
            {
                _player.x -= _player.speed;
                _player.y -= _player.gravity;
                _player.width = 65;
                _player.height = 145;
                if (fabs(_player.preX - _player.x) >= 70)
                {
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = JUMP;
                    _player.jumpTimer = _player.jumpTimeLimit / 2;
                }
            }
            //=======================================================//
            // 평타 칠 때
            if (_player.atkType == NORMAL_ATTACK)
            {
                _player.width = 115;
                _player.height = 110;
                _player.y = _player.attackY + 25;
                if (_player.dirType == LEFT)
                {
                    _player.atkRc = RectMakeCenter(_player.x - 20, _player.y - 100, 520, 300);
                }
                else if (_player.dirType == RIGHT)
                {
                    _player.atkRc = RectMakeCenter(_player.x + 20, _player.y - 100, 520, 300);
                }
            }
        }
        else
        {
            // 땅에서 왼쪽 대쉬할 때
            if (_player.dirType == LEFT && _player.atkType == DASH_GROUND)
            {
                _player.width = 115;
                _player.height = 80;
                _player.y = _player.dashY + 40;

                _player.dashRcWidth = 120;
                _player.dashRcHeight = 50;
                _player.dashRcX = _player.rc.left - _player.dashRcWidth / 2;
                _player.dashRcY = _player.y;

                if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_2") ||
                    _player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_2"))
                {
                    _player.x -= DASHSPEED;
                    _player.dashRcX -= DASHSPEED;
                }

                if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                {
                    if (!_player.curPlayAtkAni->isPlay())
                    {
                        _player.dirType = LEFT;
                        _player.posType = ONTHEGROUND;
                        _player.stateType = IDLE_NORMAL;
                        _player.jumpType = NON_JUMP;
                        _player.atkType = NON_ATTACK;
                    }
                }
            }
            // 땅에서 오른쪽 대쉬할 때
            else if (_player.dirType == RIGHT && _player.atkType == DASH_GROUND)
            {
                _player.width = 115;
                _player.height = 80;
                _player.y = _player.dashY + 40;

                _player.dashRcWidth = 120;
                _player.dashRcHeight = 50;
                _player.dashRcX = _player.rc.right + _player.dashRcWidth / 2;
                _player.dashRcY = _player.y;

                if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_2") ||
                    _player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_2"))
                {
                    _player.x += DASHSPEED;
                    _player.dashRcX += DASHSPEED;
                }

                if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                {
                    if (!_player.curPlayAtkAni->isPlay())
                    {
                        _player.dirType = RIGHT;
                        _player.posType = ONTHEGROUND;
                        _player.stateType = IDLE_NORMAL;
                        _player.jumpType = NON_JUMP;
                        _player.atkType = NON_ATTACK;
                    }
                }
            }
            // 공중에서 왼쪽 대쉬할 때, 매달렸다가 대쉬할 때
            if (_player.dirType == LEFT && _player.atkType == DASH_AIR)
            {
                _player.width = 115;
                _player.height = 110;
                _player.y = _player.dashY;

                _player.dashRcWidth = 130;
                _player.dashRcHeight = 50;
                _player.dashRcX = _player.rc.left - _player.dashRcWidth / 2;
                _player.dashRcY = _player.y + 25;

                if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_left_2") ||
                    _player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_left_2"))
                {
                    _player.x -= DASHSPEED;
                }

                if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                {
                    if (!_player.curPlayAtkAni->isPlay())
                    {
                        _player.dirType = LEFT;
                        _player.posType = INTHEAIR;
                        _player.stateType = IDLE_NORMAL;
                        _player.jumpType = LAND;
                        _player.atkType = NON_ATTACK;
                    }
                }
            }
            // 공중에서 오른쪽 대쉬할 때, 매달렸다가 대쉬할 때
            else if (_player.dirType == RIGHT && _player.atkType == DASH_AIR)
            {
                _player.width = 115;
                _player.height = 110;
                _player.y = _player.dashY;

                _player.dashRcWidth = 130;
                _player.dashRcHeight = 50;
                _player.dashRcX = _player.rc.right + _player.dashRcWidth / 2;
                _player.dashRcY = _player.y + 25;

                if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_ground_right_2") ||
                    _player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_dash_air_right_2"))
                {
                    _player.x += DASHSPEED;
                }

                if (fabs(_player.dashX - _player.x) >= DASHLENGTH)
                {
                    if (!_player.curPlayAtkAni->isPlay())
                    {
                        _player.dirType = RIGHT;
                        _player.posType = INTHEAIR;
                        _player.stateType = IDLE_NORMAL;
                        _player.jumpType = LAND;
                        _player.atkType = NON_ATTACK;
                    }
                }
            }
            // 창던질 때
            if (_player.posType == ONTHEGROUND && _player.atkType == THROW)
            {
                _player.width = 90;
                _player.height = 120;
                _player.y = _player.throwY + 20;
                if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_left_3") &&
                    !ANIMATIONMANAGER->findAnimation("hornet_throw_left_3")->isPlay())
                {
                    _player.dirType = LEFT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = NON_ATTACK;
                }
                else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_throw_right_3") &&
                    !ANIMATIONMANAGER->findAnimation("hornet_throw_right_3")->isPlay())
                {
                    _player.dirType = RIGHT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = NON_ATTACK;
                }
            }
            // 땅에서 스플래쉬 공격
            if (_player.posType == ONTHEGROUND && _player.atkType == SPLASH_GROUND)
            {
                _player.width = 100;
                _player.height = 120;
                _player.y = _player.splashY + 20;

                _player.splashRc = RectMakeCenter(_player.x, _player.y - 20, _player.splashRcWidth, _player.splashRcHeight);

                if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3") &&
                    !ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3")->isPlay())
                {
                    _player.dirType = LEFT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = NON_ATTACK;
                }
                else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3") &&
                    !ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3")->isPlay())
                {
                    _player.dirType = RIGHT;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.atkType = NON_ATTACK;
                }
            }
            // 공중에서 스플래쉬 공격
            else if (_player.posType == INTHEAIR && _player.atkType == SPLASH_AIR)
            {
                _player.width = 100;
                _player.height = 120;
                _player.y = _player.splashY + 20;

                _player.splashRc = RectMakeCenter(_player.x, _player.y - 20, _player.splashRcWidth, _player.splashRcHeight);

                if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3") &&
                    !ANIMATIONMANAGER->findAnimation("hornet_splashAttack_left_3")->isPlay())
                {
                    _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                    _player.atkType = NON_ATTACK;
                }
                else if (_player.curPlayAtkAni == ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3") &&
                    !ANIMATIONMANAGER->findAnimation("hornet_splashAttack_right_3")->isPlay())
                {
                    _player.dirType = RIGHT;
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                    _player.atkType = NON_ATTACK;
                }
            }
        }

        // RECT 사이즈 보정
        // 땅위에서 가만히 있을 때
        if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL &&
            _player.jumpType == NON_JUMP && _player.atkType == NON_ATTACK)
        {
            _player.width = 65;
            _player.height = 160;
        }
    }

    _player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);

    //=======================캐릭터 위치 보정=======================//    
    // 비-공격/평타 중일 때
    if (_player.atkType == NON_ATTACK || _player.atkType == NORMAL_ATTACK)
    {
        //=======================platform 왼쪽=======================//
        // 땅에서 달리는데 왼쪽에 벽이 있을 때
        if (_player.dirType == LEFT && _player.posType == ONTHEGROUND &&
            _player.stateType == RUN && _player.jumpType == NON_JUMP)
        {
            if (pixelCheckLeft())
            {
                _player.dirType = LEFT;
                _player.posType = ONTHEGROUND;
                _player.stateType = RUN;
                _player.jumpType = NON_JUMP;
            }
        }
        // 공중에서 달리는데 왼쪽에 벽이 있을 때
        else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
            _player.stateType == RUN && _player.jumpType == JUMP)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (_player.rc.right > tempCheck.objectRect.right)
                {
                    _player.x = tempCheck.objectRect.right + _player.width / 2;
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = JUMP;
                }
            }
            else
            {
                if (pixelCheckLeft())
                {
                    _player.dirType = LEFT;
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = JUMP;
                }
            }
        }
        // 낙하 중에 달리는데 왼쪽에 벽이 있어 매달릴 때
        else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
            _player.stateType == RUN && _player.jumpType == LAND)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (_player.rc.right > tempCheck.objectRect.right)
                {
                    _player.x = tempCheck.objectRect.right + _player.width / 2;
                    _player.dirType = LEFT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                }
            }
            else
            {
                if (pixelCheckLeft())
                {
                    _player.dirType = LEFT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                }
            }
        }
        // 왼쪽으로 벽 점프했는데 벽이 있을 경우
        else if (_player.dirType == LEFT && _player.posType == INTHEAIR &&
            _player.stateType == RUN && _player.jumpType == WALL_JUMP)
        {
            if (pixelCheckLeft())
            {
                _player.dirType = LEFT;
                _player.posType = HANGING;
                _player.stateType = HANG;
                _player.jumpType = NON_JUMP;
                _player.airDashCount = 0;
            }
        }
        // 왼쪽 벽에 매달려 있다가 떨어지는데 공중일 경우
        else if (_player.dirType == LEFT && _player.posType == HANGING &&
            _player.stateType == HANG && _player.jumpType == NON_JUMP)
        {
            if (!pixelCheckLeft() && !pixelCheckDown())
            {
                _player.dirType = LEFT;
                _player.posType = INTHEAIR;
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) _player.stateType = RUN;
                else _player.stateType = IDLE_NORMAL;
                _player.jumpType = LAND;
                _player.airDashCount = 0;
            }
        }
        //=======================platform 오른쪽=======================//
        // 땅에서 달리는데 오른쪽에 벽이 있을 때
        if (_player.dirType == RIGHT && _player.posType == ONTHEGROUND &&
            _player.stateType == RUN && _player.jumpType == NON_JUMP)
        {
            if (pixelCheckRight())
            {
                _player.dirType = RIGHT;
                _player.posType = ONTHEGROUND;
                _player.stateType = RUN;
                _player.jumpType = NON_JUMP;
            }

        }
        // 공중에서 달리는데 오른쪽에 벽이 있을 때
        else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
            _player.stateType == RUN && _player.jumpType == JUMP)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (_player.rc.left < tempCheck.objectRect.left)
                {
                    _player.x = tempCheck.objectRect.left - _player.width / 2;
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = JUMP;
                }
            }
            else
            {
                if (pixelCheckRight())
                {
                    _player.dirType = RIGHT;
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = JUMP;
                }
            }
        }
        // 낙하 중에 달리는데 오른쪽에 벽이 있어 매달릴 때
        else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
            _player.stateType == RUN && _player.jumpType == LAND)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (_player.rc.left < tempCheck.objectRect.left)
                {
                    _player.x = tempCheck.objectRect.left - _player.width / 2;
                    _player.dirType = RIGHT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                }
            }
            else
            {
                if (pixelCheckRight())
                {
                    _player.dirType = RIGHT;
                    _player.posType = HANGING;
                    _player.stateType = HANG;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                }
            }
        }
        // 오른쪽으로 벽 점프했는데 벽이 있을 경우
        else if (_player.dirType == RIGHT && _player.posType == INTHEAIR &&
            _player.stateType == RUN && _player.jumpType == WALL_JUMP)
        {
            if (pixelCheckRight())
            {
                _player.dirType = RIGHT;
                _player.posType = HANGING;
                _player.stateType = HANG;
                _player.jumpType = NON_JUMP;
                _player.airDashCount = 0;
            }
        }
        // 오른쪽 벽에 매달려 있다가 떨어지는데 공중일 경우
        else if (_player.dirType == RIGHT && _player.posType == HANGING &&
            _player.stateType == HANG && _player.jumpType == NON_JUMP)
        {
            if (!pixelCheckRight() && !pixelCheckDown())
            {
                _player.dirType = RIGHT;
                _player.posType = INTHEAIR;
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) _player.stateType = RUN;
                else _player.stateType = IDLE_NORMAL;
                _player.jumpType = LAND;
                _player.airDashCount = 0;
            }
        }
        //=======================platform 아래=======================//
        // 제자리 점프하는데 위에 장애물이 있을 경우
        if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL &&
            _player.jumpType == JUMP)
        {
            if (pixelCheckUp())
            {
                _player.posType = INTHEAIR;
                _player.stateType = IDLE_NORMAL;
                _player.jumpType = LAND;
            }
        }
        // 달리기 점프하는데 위에 장애물이 있을 경우
        else if (_player.posType == INTHEAIR && _player.stateType == RUN &&
            _player.jumpType == JUMP)
        {
            if (pixelCheckUp())
            {
                _player.posType = INTHEAIR;
                _player.stateType = RUN;
                _player.jumpType = LAND;
            }
        }

        //=======================platform 위=======================//
        // 땅 위에 서 있을 때 체크
        if (_player.posType == ONTHEGROUND && _player.stateType == IDLE_NORMAL && _player.jumpType == NON_JUMP)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (_player.rc.top < tempCheck.objectRect.top)
                {
                    _player.y = tempCheck.objectRect.top - _player.height / 2;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                }
            }
            else
            {
                if (pixelCheckDown())
                {
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                }
                else
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }

            }
        }
        // 땅 위에서 움직일 때 체크
        else if (_player.posType == ONTHEGROUND && _player.stateType == RUN && _player.jumpType == NON_JUMP)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (_player.rc.top < tempCheck.objectRect.top)
                {
                    _player.y = tempCheck.objectRect.top - _player.height / 2;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = RUN;
                    _player.jumpType = NON_JUMP;
                }
            }
            if (pixelCheckDown())
            {
                _player.posType = ONTHEGROUND;
                _player.stateType = RUN;
                _player.jumpType = NON_JUMP;
            }
            else
            {
                _player.posType = INTHEAIR;
                _player.stateType = RUN;
                _player.jumpType = LAND;
            }
        }
        // 낙하 중 가만히 있을 때 체크
        else if (_player.posType == INTHEAIR && _player.stateType == IDLE_NORMAL && _player.jumpType == LAND)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (tempCheck.objectRect.top > _player.rc.top)
                {
                    _player.y = tempCheck.objectRect.top - _player.height / 2;
                    _player.atkType = NON_ATTACK;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                    _player.airSplashCount = 0;
                }
            }
            else
            {
                if (pixelCheckDown())
                {
                    _player.posType = ONTHEGROUND;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                    _player.airSplashCount = 0;
                }
                else
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = IDLE_NORMAL;
                    _player.jumpType = LAND;
                }
            }
        }
        // 낙하 중 움직이고 있을 때 체크
        else if (_player.posType == INTHEAIR && _player.stateType == RUN && _player.jumpType == LAND)
        {
            tagCollisionCheck tempCheck;
            tempCheck = rectCollision();
            if (tempCheck.boolValue)
            {
                if (tempCheck.objectRect.top > _player.rc.top)
                {
                    _player.y = tempCheck.objectRect.top - _player.height / 2;
                    _player.atkType = NON_ATTACK;
                    _player.posType = ONTHEGROUND;
                    _player.stateType = RUN;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                    _player.airSplashCount = 0;
                }
            }
            else
            {
                if (pixelCheckDown())
                {
                    _player.posType = ONTHEGROUND;
                    _player.stateType = RUN;
                    _player.jumpType = NON_JUMP;
                    _player.airDashCount = 0;
                    _player.airSplashCount = 0;
                }
                else
                {
                    _player.posType = INTHEAIR;
                    _player.stateType = RUN;
                    _player.jumpType = LAND;
                }
            }
        }
        // 벽에 매달린 상태에서 땅에 닿았을 때 체크
        else if (_player.posType == HANGING && _player.stateType == HANG && _player.jumpType == NON_JUMP)
        {
            if (pixelCheckDown())
            {
                _player.posType = ONTHEGROUND;
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) _player.stateType = RUN;
                else _player.stateType = IDLE_NORMAL;
                _player.jumpType = NON_JUMP;
            }
            else
            {
                _player.posType = HANGING;
                _player.stateType = HANG;
                _player.jumpType = NON_JUMP;
            }
        }
    }



    // 점프 타이머/카운트 리셋
    if (!(GetAsyncKeyState('C') & 0x8000) && _player.posType == ONTHEGROUND)
    {
        _player.jumpTimer = 0;
        _player.jumpCount = 0;
    }

    _player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
    _player.dashRc = RectMakeCenter(_player.dashRcX, _player.dashRcY, _player.dashRcWidth, _player.dashRcHeight);
}


