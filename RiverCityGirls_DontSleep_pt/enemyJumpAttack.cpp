#include "stdafx.h"
#include "enemyJumpAttack.h"
#include "Enemy.h"

void enemyJumpAttack::EnterState()
{
	SOUND_M->playSFX("enemy_jumpattack");
	_thisEn->SetImage();
	_thisEn->getInfo().isSky = true;
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

void enemyJumpAttack::UpdateState()
{

	Attack();

	if (_thisEn->getObj()->pos.y > 0)
	{
		_thisEn->getObj()->pos.y = 0;
	}
	if (_thisEn->getObj()->pos.y == 0)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	
}

void enemyJumpAttack::ExitState()
{
	_thisEn->getInfo().jumpPower = 0;
	_thisEn->getInfo().isSky = false;
	_thisEn->getInfo().isAttack = false;
}
