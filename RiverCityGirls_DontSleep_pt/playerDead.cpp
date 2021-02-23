#include "stdafx.h"
#include "playerDead.h"


void playerDead::EnterState()
{
	//무기떨어뜨리기
	dropWeapon();

	//넘어져있었으면 바로 죽음이미지로 변경
	if (_thisPl->getInfo().preState == PL_STATE::DOWN)
	_thisPl->changeImg("pl_dead", false);

	//사망
	_thisPl->getInfo().isDead = true;

	//키조작 불가
	_thisPl->setIsControl(false);

	//알파값보정
	_thisPl->getRefObj().alpha = 255;

	//시간값 초기화
	_stateTimer = TIME_M->getWorldTime();
}

void playerDead::UpdateState()
{
	if (TIME_M->getWorldTime() - _stateTimer > 4.f && _thisPl->getInfo().preState == PL_STATE::DOWN)
	{
		if (_thisPl->getStageM()->getCurStage() == STAGETYPE::BOSS)
		{
			UI_M->popUI("bossHPBar1");
			UI_M->popUI("bossHPBar2");
		}
		EVENT_M->addEvent(new heart(true));
		DATA_M->loadStageData();
		_thisPl->getInfo().isDead = false;
		_thisPl->setIsControl(true);
	}

	//넘어져있지 않았다면 넘어뜨림
	if (_thisPl->getInfo().preState != PL_STATE::DOWN )
		_thisPl->setState(PL_STATE::DOWN);

	//죽은상태고 프레임이 다돌면 재시작 불 값이 켜짐
	if (isEndFrame(false) && _thisPl->getInfo().isDead && !_thisPl->getInfo().isRestart)_thisPl->getInfo().isRestart = true;

}

void playerDead::ExitState()
{

}
