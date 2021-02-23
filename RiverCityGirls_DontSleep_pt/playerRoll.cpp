#include "stdafx.h"
#include "playerRoll.h"

void playerRoll::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_roll",false);
	//키조작 불가로 변겅
	_thisPl->setIsControl(false);

	//이뮨상태
	_thisPl->getInfo().isImmune = true;
}

void playerRoll::UpdateState()
{
	//이동
	if (_thisPl->getInfo().dest == DIRECTION::LEFT)
		_thisPl->movePos(-_thisPl->getInfo().speed*2.5, 0, 0);
	if (_thisPl->getInfo().dest == DIRECTION::RIGHT)
		_thisPl->movePos(_thisPl->getInfo().speed*2.5, 0, 0);
	
	//이뮨상태 + 알파값 수정
	_thisPl->getPObj()->alpha = 160;
	
	//프레임이 끝나면 키조작 허용
	if (isEndFrame(false))
	{
		_thisPl->setIsControl(true);
		_thisPl->getInfo().isImmune = false;
		_thisPl->getPObj()->alpha = 255;
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerRoll::ExitState()
{
}
