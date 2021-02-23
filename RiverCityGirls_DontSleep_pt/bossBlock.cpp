#include "stdafx.h"
#include "bossBlock.h"
#include "Boss.h"

void bossBlock::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_block");
	SOUND_M->playSFX("bblock");
	LookatPlayer();
	ResetFrame();
}

void bossBlock::UpdateState()
{
}

void bossBlock::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	
}
