#include "stdafx.h"
#include "bossStandAttack.h"

void bossStandAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_standat");
	SOUND_M->playSFX("bstand");
	_thisBs->getInfo().isAttack = true;
	_isEffect = false;
	LookatPlayer();
	ResetFrame();
}

void bossStandAttack::UpdateState()
{
	if (!_thisBs->getIsphase())
	{
		if (TIME_M->getWorldTime() - _enterTime > 0.5f && _thisBs->getInfo().isAttack)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
		}

		if (!_isEffect && TIME_M->getWorldTime() - _enterTime > 0.5f)
		{
			EFFECT_M->play("Bss_stand", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z + 200);
			_isEffect = true;
		}
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);

		if (TIME_M->getWorldTime() - _enterTime > 0.5f && _thisBs->getInfo().isAttack)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
		}

		if (!_isEffect && TIME_M->getWorldTime() - _enterTime > 0.5f)
		{
			EFFECT_M->play("Bss_stand", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z + 200);
			_isEffect = true;
		}
	}
}


void bossStandAttack::ExitState()
{
	_thisBs->getInfo().isAttack = false;
	_thisBs->SetState(BS_STATE::IDLE);
}
