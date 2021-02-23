#include "stdafx.h"
#include "playerRun.h"

void playerRun::EnterState()
{
	//이미지 변경
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatRun", true);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}
	}
	else _thisPl->changeImg("pl_run", true);

	//방향에 따른 이팩트 실행
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		EFFECT_M->play("ef_runL", _thisPl->getObj().rc.right, _thisPl->getObj().rc.bottom);
		break;
	case DIRECTION::RIGHT:
		EFFECT_M->play("ef_runR", _thisPl->getObj().rc.left,_thisPl->getObj().rc.bottom);
		break;
	}



	//키조작 가능
	_thisPl->setIsControl(true);
	//방향전환 가능
	_thisPl->getInfo().isConDest = true;
}

void playerRun::UpdateState()
{
	//키를 안 누르면 기본상태
	if (!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->setState(PL_STATE::IDLE);

	//이동
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);

	//약공격
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::DASHATTACK);

	//강공격
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::DASHSATTACK);


}

void playerRun::ExitState()
{
}
