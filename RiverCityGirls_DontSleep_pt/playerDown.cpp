#include "stdafx.h"
#include "playerDown.h"

void playerDown::EnterState()
{
	SOUND_M->playSFX("kyoko_down");

	//이뮨상태로 만들기
	_thisPl->getInfo().isImmune = true;
	_thisPl->getRefObj().alpha = 180;

	//이미지변경
	_thisPl->changeImg("pl_down", false);

	//무기떨어뜨리기
	dropWeapon();

	_thisPl->setIsControl(false);
}

void playerDown::UpdateState()
{
	if (isEndFrame(false) && !_thisPl->getInfo().isDead)
	{
		_thisPl->setState(PL_STATE::STAND);
		_thisPl->setIsControl(true);
	}

	if (isEndFrame(false) && _thisPl->getInfo().isDead)_thisPl->setState(PL_STATE::DEAD);
}

void playerDown::ExitState()
{
	_thisPl->setIsControl(true);

}
