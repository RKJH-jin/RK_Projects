#include "stdafx.h"
#include "playerHit.h"
#include "EnemyManager.h"
#include "Enemy.h"


void playerHit::EnterState()
{
	RECT temp;

	SOUND_M->playSFX("kyoko_hit");

	//이뮨상태로 만들기
	_thisPl->getInfo().isImmune = true;
	_thisPl->getRefObj().alpha = 180;

	//맞은수 세기
	_thisPl->getInfo().hitCount++;

	//이미지변경
	_thisPl->changeImg("pl_hit", false);

	//키조작불가
	_thisPl->setIsControl(false);

	

	//무기떨어뜨리기
	dropWeapon();
}

void playerHit::UpdateState()
{

	//프레임이 끝나면 키조작 허용
	if (isEndFrame(false))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerHit::ExitState()
{
	_thisPl->setIsControl(true);

}
