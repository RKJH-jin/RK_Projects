#include "stdafx.h"
#include "playerJump.h"

void playerJump::EnterState()
{
	//이미지 변경
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatJump", true);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}
	}
	else _thisPl->changeImg("pl_jump", true);

	
}

void playerJump::UpdateState()
{
	//이동
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed/2);

	//약공격
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::JUMPATTACK);
}

void playerJump::ExitState()
{
}
