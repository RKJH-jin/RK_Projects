#include "stdafx.h"
#include "playerClimbTop.h"

void playerClimbTop::EnterState()
{

	_thisPl->setIsControl(false);
	if(_thisPl->getInfo().moveDest == MOVE_DIRECTION::DOWN)
	_thisPl->changeImg("pl_climbTopDown", false);
	 if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::UP)
	_thisPl->changeImg("pl_climbTop", false);

	 _thisPl->getInfo().dest = DIRECTION::LEFT;
	
}

void playerClimbTop::UpdateState()
{
	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::DOWN
		&& isEndFrame(false))
		{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::CLIMB);
		}
	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::UP
		&& isEndFrame(false))
		{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
		}
}

void playerClimbTop::ExitState()
{

}
