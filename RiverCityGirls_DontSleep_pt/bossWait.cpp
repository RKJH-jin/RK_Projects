#include "stdafx.h"
#include "bossWait.h"

void bossWait::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_idle");
	_thisBs->getInfo().isAttack = false;
	ResetFrame();
}

void bossWait::UpdateState()
{
	LookatPlayer();

	if (_thisBs->getState() != BS_STATE::DEATH && _thisBs->getState() != BS_STATE::BLOCK && _thisBs->getState() != BS_STATE::PHASE)
	{
		RECT _temp;
		if (IntersectRect(&_temp, &_thisBs->getObj()->rc, &_thisBs->getPlayerAddress()->getInfo().attackRc) && !_thisBs->getInfo().isAttack && _thisBs->getPlayerAddress()->getInfo().isAttack)
		{
			Damaged(_thisBs->getPlayerAddress()->getInfo().force);
		}
	}

	if (!_thisBs->getIsphase())
	{
		if (fabs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getObj()->pos.x) < 120 && fabs(_thisBs->getPlayerAddress()->getObj().pos.z - _thisBs->getObj()->pos.z) < 30
			&& TIME_M->getWorldTime() - _enterTime > 0.7f)
		{
			switch (RND->getInt(4))
			{
			case 0:
				_thisBs->SetState(BS_STATE::SLAP);
				break;
			case 1:
				_thisBs->SetState(BS_STATE::ELBOW);
				break;
			case 2:
				_thisBs->SetState(BS_STATE::BLOCK);
				break;
			case 3:
				_thisBs->SetState(BS_STATE::HOWLING);
				break;
			}
		}

		else if (fabs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 30 && fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30)
		{
			_thisBs->SetState(BS_STATE::MOVE);
		}
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);

		if (_thisBs->getIsphase())
		{
			switch (RND->getInt(4))
			{
			case 0:
				_thisBs->SetState(BS_STATE::SMASH);
				break;
			case 1:
				_thisBs->SetState(BS_STATE::ELBOW);
				break;
			case 2:
				_thisBs->SetState(BS_STATE::BLOCK);
				break;
			case 3:
				_thisBs->SetState(BS_STATE::HOWLING);
				break;
			}
		}

		else if (fabs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 30 && fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30)
		{
			_thisBs->SetState(BS_STATE::MOVE);
		}
	}
}

void bossWait::ExitState()
{
}