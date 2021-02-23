#include "stdafx.h"
#include "enemyStun.h"
#include "Enemy.h"

void enemyStun::EnterState()
{
	SOUND_M->playSFX("enemy_stun");
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
	EFFECT_M->play("ef_stun", (_thisEn->getRefObj().rc.left + _thisEn->getRefObj().rc.right) / 2, _thisEn->getRefObj().rc.top);

}

void enemyStun::UpdateState()
{
	if(TIME_M->getWorldTime() - _stateTimer > 2.0f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyStun::ExitState()
{
}
