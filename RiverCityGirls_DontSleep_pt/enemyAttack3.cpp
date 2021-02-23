#include "stdafx.h"
#include "enemyAttack3.h"
#include "Enemy.h"

void enemyAttack3::EnterState()
{
	SOUND_M->playSFX("enemy_attack3");
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

void enemyAttack3::UpdateState()
{
	Attack();

	//ATTACK3의 상태가 끝났다.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}

}

void enemyAttack3::ExitState()
{
	_thisEn->getInfo().isAttack = false;
}
