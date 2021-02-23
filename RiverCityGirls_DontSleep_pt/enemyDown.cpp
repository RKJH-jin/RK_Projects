#include "stdafx.h"
#include "enemyDown.h"
#include "Enemy.h"

void enemyDown::EnterState()
{
	SOUND_M->playSFX("enemy_down");
	isDown = true;
	_thisEn->SetImage();
	_thisEn->getInfo().isSky = true;
}

void enemyDown::UpdateState()
{
	LookAtPlayer();
	_thisEn->xzyMove(0, 0, -10.0f);

	//HIT의 상태가 끝났다.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyDown::ExitState()
{
	isDown = false;
	_thisEn->getInfo().isSky = false;
}
