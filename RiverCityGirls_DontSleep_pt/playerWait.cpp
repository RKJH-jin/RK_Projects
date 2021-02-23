#include "stdafx.h"
#include "playerWait.h"

void playerWait::EnterState()
{
	_thisPl->changeImg("pl_wait",false);
}

void playerWait::UpdateState()
{
	//프레임이 끝났으면 일반 상태로 전환
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
	
	//업데이트 정지 유무
	if (pauseUpdate())return;
	
	//기본동작
	basePattern();

	//강공격
	sAttack();

}

void playerWait::ExitState()
{
}
