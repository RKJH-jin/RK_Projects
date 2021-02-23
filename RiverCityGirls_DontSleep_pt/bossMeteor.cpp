#include "stdafx.h"
#include "bossMeteor.h"
#include "Boss.h"
#include "Player.h"

void bossMeteor::EnterState()
{
	_angle = PI / 2;
	_speed = 25.0f;
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_meteor");
	SOUND_M->playSFX("bmeteor");
	_thisBs->getInfo().jumpPower = 18.0f;
	_thisBs->getInfo().isSky = true;
	_isEffect = false;
	LookatPlayer();
	ResetFrame();

}

void bossMeteor::UpdateState()
{
	if (!_thisBs->getIsphase())
	{
		if (0.5f < TIME_M->getWorldTime() - _enterTime && TIME_M->getWorldTime() - _enterTime <= 2.5f) // 하늘 위로 올라가는 시간
		{
			_thisBs->xzyMove(0, 0, -_thisBs->getInfo().jumpPower);
			if (_thisBs->getObj()->pos.y < -600) _thisBs->getObj()->pos.y = -600;
		}

		if (2.5f < TIME_M->getWorldTime() - _enterTime && TIME_M->getWorldTime() - _enterTime <= 3.0f) // 하늘 위에서 움직이는 시간
		{
			_thisBs->ChangeImg("Bs_meteordown");

			if (_thisBs->getInfo().dest == DIRECTION::LEFT && _thisBs->getObj()->imgIndex.x <= 0) _thisBs->getObj()->imgIndex.x = 1;
			else if (_thisBs->getInfo().dest == DIRECTION::RIGHT && _thisBs->getObj()->imgIndex.x >= 1) _thisBs->getObj()->imgIndex.x = 0;

			_thisBs->xzyMove(cosf(_angle) * _speed, -sinf(_angle) * _speed, 0);
			_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
				_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		}

		if (4.0f < TIME_M->getWorldTime() - _enterTime) // 떨어지는 시간
		{
			_thisBs->getInfo().isAttack = true;

			if (_thisBs->getInfo().dest == DIRECTION::LEFT && _thisBs->getObj()->imgIndex.x <= 0)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
				_thisBs->getObj()->imgIndex.x = 1;
			}
			else if (_thisBs->getInfo().dest == DIRECTION::RIGHT && _thisBs->getObj()->imgIndex.x >= 1)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
				_thisBs->getObj()->imgIndex.x = 0;
			}

			if (_thisBs->getInfo().isSky)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
				_thisBs->xzyMove(0, 0, 80.0f);
				if (!_isEffect)
				{
					EFFECT_M->play("Bss_meteor", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
						(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
				}
			}

			if (_thisBs->getObj()->pos.y >= 0)
			{
				_thisBs->getInfo().isAttack = false;
				_thisBs->SetState(BS_STATE::DOWN);
				_thisBs->getObj()->pos.y = 0;
				_thisBs->getInfo().isSky = false;
			}
		}
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);

		if (0.5f < TIME_M->getWorldTime() - _enterTime && TIME_M->getWorldTime() - _enterTime <= 2.5f) // 하늘 위로 올라가는 시간
		{
			_thisBs->xzyMove(0, 0, -_thisBs->getInfo().jumpPower);
			if (_thisBs->getObj()->pos.y < -600) _thisBs->getObj()->pos.y = -600;
		}

		if (2.5f < TIME_M->getWorldTime() - _enterTime && TIME_M->getWorldTime() - _enterTime <= 3.0f) // 하늘 위에서 움직이는 시간
		{
			_thisBs->ChangeImg("Bs_meteordown");

			if (_thisBs->getInfo().dest == DIRECTION::LEFT && _thisBs->getObj()->imgIndex.x <= 0) _thisBs->getObj()->imgIndex.x = 1;
			else if (_thisBs->getInfo().dest == DIRECTION::RIGHT && _thisBs->getObj()->imgIndex.x >= 1) _thisBs->getObj()->imgIndex.x = 0;

			_thisBs->xzyMove(cosf(_angle) * _speed, -sinf(_angle) * _speed, 0);
			_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
				_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		}

		if (4.0f < TIME_M->getWorldTime() - _enterTime) // 떨어지는 시간
		{
			_thisBs->getInfo().isAttack = true;

			if (_thisBs->getInfo().dest == DIRECTION::LEFT && _thisBs->getObj()->imgIndex.x <= 0)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
				_thisBs->getObj()->imgIndex.x = 1;
			}
			else if (_thisBs->getInfo().dest == DIRECTION::RIGHT && _thisBs->getObj()->imgIndex.x >= 1)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
				_thisBs->getObj()->imgIndex.x = 0;
			}

			if (_thisBs->getInfo().isSky)
			{
				_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
				_thisBs->xzyMove(0, 0, 80.0f);
				if (!_isEffect)
				{
					EFFECT_M->play("Bss_meteor", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
						(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
				}
			}

			if (_thisBs->getObj()->pos.y >= 0)
			{
				_thisBs->getInfo().isAttack = false;
				_thisBs->SetState(BS_STATE::DOWN);
				_thisBs->getObj()->pos.y = 0;
				_thisBs->getInfo().isSky = false;
			}
		}
	}
}

void bossMeteor::ExitState()
{
	_thisBs->getInfo().isAttack = false;
	_isEffect = true;
}
