#include "stdafx.h"
#include "bossHowling.h"
#include "Boss.h"
#include "Player.h"

void bossHowling::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_howling");
	SOUND_M->playSFX("bhowling");
	_thisBs->getInfo().isAttack = true;
	LookatPlayer();
	ResetFrame();
}

void bossHowling::UpdateState()
{
	if (!_thisBs->getIsphase())
	{
		if (_thisBs->getInfo().isAttack)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150, 300, 300);
		}

		if (TIME_M->getWorldTime() - _enterTime > 0.6f)
		{
			EFFECT_M->play("Bss_howling", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
				_thisBs->getInfo().rcAttack.bottom);

			EFFECT_M->play("Bss_howling2", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
				(_thisBs->getInfo().rcAttack.bottom + _thisBs->getInfo().rcAttack.top) / 2);
		}
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);

		if (_thisBs->getInfo().isAttack)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150, 300, 300);
		}

		if (TIME_M->getWorldTime() - _enterTime > 0.6f)
		{
			EFFECT_M->play("Bss_howling", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
				_thisBs->getInfo().rcAttack.bottom);

			EFFECT_M->play("Bss_howling2", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
				(_thisBs->getInfo().rcAttack.bottom + _thisBs->getInfo().rcAttack.top) / 2);
		}
	}
}

void bossHowling::ExitState()
{
	_thisBs->getInfo().isAttack = false;

	switch (RND->getInt(2))
	{
	case 0:
		_thisBs->SetState(BS_STATE::METEOR);
		break;
	case 1:
		_thisBs->SetState(BS_STATE::DASH);
		break;
	}
}
