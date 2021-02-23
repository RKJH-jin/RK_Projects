#include "stdafx.h"
#include "bossSlapAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSlapAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_slap");
	SOUND_M->playSFX("bslap");
	_thisBs->getInfo().isAttack = true;
	_isEffect = false;
	LookatPlayer();
	ResetFrame();
}

void bossSlapAttack::UpdateState()
{
	if (!_thisBs->getIsphase())
	{
		if (_thisBs->getInfo().isAttack && TIME_M->getWorldTime() - _enterTime > 0.9f)
		{
			if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
			{
				_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->pos.x + 70, _thisBs->getObj()->pos.z - 200, 150, 200);
			}
			else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
			{
				_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->pos.x - 200, _thisBs->getObj()->pos.z - 200, 150, 200);
			}
		}
		RECT _temp;
		if (!_isEffect && IntersectRect(&_temp, &_thisBs->getInfo().rcAttack, &_thisBs->getPlayerAddress()->getRefObj().rc) && TIME_M->getWorldTime() - _enterTime > 0.9f)
		{
			EFFECT_M->play("ef_attack", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
				(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
			_isEffect = true;
		}
	}
}

void bossSlapAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
