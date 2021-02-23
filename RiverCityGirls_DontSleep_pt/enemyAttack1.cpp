#include "stdafx.h"
#include "enemyAttack1.h"
#include "EnemyManager.h"
#include "Enemy.h"

void enemyAttack1::EnterState()
{
	SOUND_M->playSFX("enemy_attack1");
	_thisEn->SetImage();
	LookAtPlayer();
	RECT temp;
	
	if (!_thisEn->getPlayerAddress()->getInfo().isImmune)
	{
		if (IntersectRect(&temp, &_thisEn->getInfo().rcAttack, &_thisEn->getPlayerAddress()->getRefObj().rc))
		{
			EFFECT_M->play("ef_attack", (_thisEn->getInfo().rcAttack.left + _thisEn->getInfo().rcAttack.right) / 2,
				(_thisEn->getInfo().rcAttack.top + _thisEn->getInfo().rcAttack.bottom) / 2);
		}
	}
}

void enemyAttack1::UpdateState()
{
	Attack();

	_thisEn->getInfo().isAttack = true;

	//ATTACK1의 상태가 끝났다.
	if (endFrame())
	{
		//가까우면 때린다.
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
			_thisEn->SetState(EN_STATE::EN_ATTACK2);
		else _thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyAttack1::ExitState()
{
	_thisEn->getInfo().isAttack = false;
}
