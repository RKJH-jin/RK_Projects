#include "stdafx.h"
#include "bossSmashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSmashAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_smash");
	SOUND_M->playSFX("bsmash");
	_thisBs->getInfo().isAttack = true;
	_isEffect = false;

	LookatPlayer();
	ResetFrame();
}

void bossSmashAttack::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 1.9f)
	{
		Attack();
	}

	RECT _temp;
	if (!_isEffect && IntersectRect(&_temp, &_thisBs->getInfo().rcAttack, &_thisBs->getPlayerAddress()->getRefObj().rc) && TIME_M->getWorldTime() - _enterTime > 1.9f)
	{
		EFFECT_M->play("Bss_smash", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
			(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
		_isEffect = true;
	}
	EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);
}

void bossSmashAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
