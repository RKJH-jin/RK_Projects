#include "stdafx.h"
#include "enemyHeldHit.h"
#include "Enemy.h"

void enemyHeldHit::EnterState()
{
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);
}

void enemyHeldHit::UpdateState()
{
	//HIT의 상태가 끝났다.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyHeldHit::ExitState()
{
}
