#include "stdafx.h"
#include "playerStick.h"

void playerStick::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_stick", false);
	_stateTimer = TIME_M->getWorldTime();
	//키조작불가
	_thisPl->setIsControl(false);
}

void playerStick::UpdateState()
{
	//시간이 지나면 떨어지고 점프가능
	if (TIME_M->getWorldTime() - _stateTimer > 1.5f)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	//점프
	if (KEY_M->isOnceKeyDownV('A'))
	{
		_thisPl->setIsSky(true);
		_thisPl->setIsControl(true);
		_thisPl->movePos(0, 0, JUMPPOWER);
		_thisPl->setJumpPower(JUMPPOWER);
		_thisPl->setState(PL_STATE::JUMP);
	}
}

void playerStick::ExitState()
{
}
