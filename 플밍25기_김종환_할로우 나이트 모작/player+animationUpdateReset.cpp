#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

void player::animationUpdateReset()
{
      //======================애니메이션 프레임 업데이트======================
    if (_player.atkType != NON_ATTACK) // 공격 모션 프레임 업데이트
    {
        if (_player.atkType == NORMAL_ATTACK)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 20);
        }
        else if (_player.atkType == DASH_AIR || _player.atkType == DASH_GROUND)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 20);
        }
        else if (_player.atkType == THROW)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
        }
        else if (_player.atkType == SPLASH_GROUND || _player.atkType == SPLASH_AIR)
        {
            _player.curPlayAtkAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 15);
        }
    }
    else if (_player.atkType == NON_ATTACK) // 이동 모션 프레임 업데이트
    {
        if (_player.stateType == PLAYER::HIT)
        {
            _player.curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
        }
        else
        {
            _player.curPlayAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
        }
    }
    
}
