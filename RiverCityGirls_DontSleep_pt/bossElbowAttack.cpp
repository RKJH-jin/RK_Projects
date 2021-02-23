#include "stdafx.h"
#include "bossElbowAttack.h"
#include "Boss.h"
#include "Player.h"

void bossElbowAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_elbow");
	SOUND_M->playSFX("belbow");
	_thisBs->getInfo().isAttack = true;
	_isEffect = false;
	LookatPlayer();
	ResetFrame();
}

void bossElbowAttack::UpdateState()
{
	if (!_thisBs->getIsphase())
	{
		RECT _temp;
		if (_thisBs->getInfo().isAttack && TIME_M->getWorldTime() - _enterTime > 0.7f)
		{
			if (_thisBs->getInfo().dest == DIRECTION::LEFT)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x - 70, _thisBs->getObj()->pos.z - 150, 200, 100);
			}

			else if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x + 70, _thisBs->getObj()->pos.z - 150, 200, 100);
			}
		}
		if (!_isEffect && IntersectRect(&_temp, &_thisBs->getInfo().rcAttack, &_thisBs->getPlayerAddress()->getRefObj().rc) && TIME_M->getWorldTime() - _enterTime > 0.6f)
		{
			EFFECT_M->play("ef_attack", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
				(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
			_isEffect = true;
		}
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);
		RECT _temp;
		if (_thisBs->getInfo().isAttack && TIME_M->getWorldTime() - _enterTime > 0.7f)
		{
			if (_thisBs->getInfo().dest == DIRECTION::LEFT)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x - 70, _thisBs->getObj()->pos.z - 150, 200, 100);
			}

			else if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x + 70, _thisBs->getObj()->pos.z - 150, 200, 100);
			}
		}
		if (!_isEffect && IntersectRect(&_temp, &_thisBs->getInfo().rcAttack, &_thisBs->getPlayerAddress()->getRefObj().rc) && TIME_M->getWorldTime() - _enterTime > 0.6f)
		{
			EFFECT_M->play("ef_attack", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
				(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
			_isEffect = true;
		}
	}
}

void bossElbowAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
