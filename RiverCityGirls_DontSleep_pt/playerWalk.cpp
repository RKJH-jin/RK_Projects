#include "stdafx.h"
#include "playerWalk.h"

void playerWalk::EnterState()
{
	//이미지 변경
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
			case WEAPON_TYPE::BAT:
				_thisPl->changeImg("pl_wBatWalk", true);
			break;
			case WEAPON_TYPE::BASEBALL:
				//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}
	}
	else _thisPl->changeImg("pl_walk", true);
	
	_stateTimer = TIME_M->getWorldTime();
	//방향변경가능상태로 전환
	_thisPl->getInfo().isConDest = true;
	//키조작 가능
	_thisPl->setIsControl(true);
}

void playerWalk::UpdateState()
{
	//한번더 누르면 대쉬
	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::LEFT &&
		KEY_M->isOnceKeyDownV(VK_LEFT))_thisPl->setState(PL_STATE::RUN);

	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::RIGHT &&
		KEY_M->isOnceKeyDownV(VK_RIGHT))_thisPl->setState(PL_STATE::RUN);

	//0.25초안에 키를 누르지 않으면 기본 상태
	if (TIME_M->getWorldTime() - _stateTimer >0.25f
		&&!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->setState(PL_STATE::IDLE);

	//이동
	lineMove(_thisPl->getInfo().speed / 2);
	crossMove(_thisPl->getInfo().speed);
}

void playerWalk::ExitState()
{
}
