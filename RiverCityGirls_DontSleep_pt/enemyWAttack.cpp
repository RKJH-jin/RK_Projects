#include "stdafx.h"
#include "enemyWAttack.h"
#include "Enemy.h"

void enemyWAttack::EnterState()
{
	SOUND_M->playSFX("enemy_wattack");
	_thisEn->SetImage();
	LookAtPlayer();
	RECT temp;
	if (IntersectRect(&temp, &_thisEn->getInfo().rcAttack, &_thisEn->getPlayerAddress()->getRefObj().rc))
	{
		if (_thisEn->getPlayerAddress()->getInfo().isImmune == false)
		{
			EFFECT_M->play("ef_attack", (_thisEn->getInfo().rcAttack.left + _thisEn->getInfo().rcAttack.right) / 2,
				(_thisEn->getInfo().rcAttack.top + _thisEn->getInfo().rcAttack.bottom) / 2);
		}
	}
}

void enemyWAttack::UpdateState()
{
	Attack();

	_thisEn->getInfo().isAttack = true;

	//WATTACK의 상태가 끝났다.
	if (endFrame())
	{
		//가까우면 때린다.
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
			_thisEn->SetState(EN_STATE::EN_WATTACK);
		else _thisEn->SetState(EN_STATE::EN_WIDLE);
	}
}

void enemyWAttack::ExitState()
{
	_thisEn->getInfo().isAttack = false;
}
