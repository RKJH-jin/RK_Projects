#include "stdafx.h"
#include "bossMove.h"
#include "Boss.h"
#include "Player.h"

void bossMove::EnterState()
{	
	_enterTime = TIME_M->getWorldTime();	 
	_angle = PI / 2;
	_speed = 3.0f;
	_thisBs->ChangeImg("Bs_move");		
	ResetFrame();
}

void bossMove::UpdateState()
{
	LookatPlayer();
	if (!_thisBs->getIsphase())
	{
		if (fabs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 30 || fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30)
		{
			_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
				_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
			_thisBs->xzyMove(cosf(_angle) * _speed, -sinf(_angle) * _speed, 0);
		}

		if (fabs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getObj()->pos.x) < 120 && fabs(_thisBs->getPlayerAddress()->getObj().pos.z - _thisBs->getObj()->pos.z) < 30)
		{
			_thisBs->SetState(BS_STATE::WAIT);
		}
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);

		if (fabs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 30 || fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30)
		{
			_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
				_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
			_thisBs->xzyMove(cosf(_angle) * _speed, -sinf(_angle) * _speed, 0);
		}
		if (fabs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getObj()->pos.x) < 120 && fabs(_thisBs->getPlayerAddress()->getObj().pos.z - _thisBs->getObj()->pos.z) < 30)
		{
			_thisBs->SetState(BS_STATE::WAIT);
		}
	}
}

void bossMove::ExitState()
{	
}
