#include "stdafx.h"
#include "playerStand.h"

void playerStand::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_stand", false);
}

void playerStand::UpdateState()
{
	if (isEndFrame(false) && !_thisPl->getInfo().isDead)
	{
		_thisPl->setState(PL_STATE::IDLE);
		_thisPl->setIsControl(true);
	}
}

void playerStand::ExitState()
{
	_thisPl->setIsControl(true);

}
