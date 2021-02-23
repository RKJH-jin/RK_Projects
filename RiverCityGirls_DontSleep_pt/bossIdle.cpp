#include "stdafx.h"
#include "bossIdle.h"
#include "Boss.h"
#include "Player.h"

void bossIdle::EnterState()
{
	_enterTime = TIME_M->getWorldTime();	
	_thisBs->ChangeImg("Bs_idle");	   
	ResetFrame();
	_thisBs->getInfo().isAttack = false;

}

void bossIdle::UpdateState()
{	
	LookatPlayer();
	if (!_thisBs->getIsphase())
	{
		if (_thisBs->getState() != BS_STATE::DEATH && _thisBs->getState() != BS_STATE::BLOCK)
		{
			RECT _temp;
			if (IntersectRect(&_temp, &_thisBs->getObj()->rc, &_thisBs->getPlayerAddress()->getInfo().attackRc) && !_thisBs->getInfo().isAttack && _thisBs->getPlayerAddress()->getInfo().isAttack)
			{
				Damaged(_thisBs->getPlayerAddress()->getInfo().force);
			}
		}
		if (TIME_M->getWorldTime() - _enterTime > 1.f)_thisBs->SetState(BS_STATE::MOVE);
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);

		if (_thisBs->getState() != BS_STATE::DEATH && _thisBs->getState() != BS_STATE::BLOCK)
		{
			RECT _temp;
			if (IntersectRect(&_temp, &_thisBs->getObj()->rc, &_thisBs->getPlayerAddress()->getInfo().attackRc) && !_thisBs->getInfo().isAttack && _thisBs->getPlayerAddress()->getInfo().isAttack)
			{
				Damaged(_thisBs->getPlayerAddress()->getInfo().force);
			}
		}
		if (TIME_M->getWorldTime() - _enterTime > 1.f)_thisBs->SetState(BS_STATE::MOVE);	
	}
}

void bossIdle::ExitState()
{
}
