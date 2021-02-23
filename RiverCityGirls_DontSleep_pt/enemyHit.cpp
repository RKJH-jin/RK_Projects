#include "stdafx.h"
#include "enemyHit.h"
#include "Enemy.h"


void enemyHit::EnterState()
{
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);

	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisEn->getObj()->imgIndex.x = 0;
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		_thisEn->getObj()->imgIndex.x = _thisEn->getObj()->img->getMaxFrameX();
	}
	
	LookAtPlayer();
	_hitIdxTimer = 0;
}

void enemyHit::UpdateState()
{
	_hitIdxTimer += TIME_M->getElapsedTime();
	if (_hitIdxTimer > 0.5f)
	{
		if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisEn->getObj()->imgIndex.x += 1;
		}
		else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
		{
			_thisEn->getObj()->imgIndex.x -= 1;
		}
		_hitIdxTimer = 0;
	}
	

	
	//HIT의 상태가 끝났다.
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		if (_thisEn->getObj()->imgIndex.x == 2)
		{
			if (_thisEn->getPlayerAddress()->getInfo().isAttack) _thisEn->SetState(EN_STATE::EN_HIT2);
			else _thisEn->SetState(EN_STATE::EN_IDLE);
			
		}
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		if (_thisEn->getObj()->imgIndex.x == 6)
		{
			if (_thisEn->getPlayerAddress()->getInfo().isAttack) _thisEn->SetState(EN_STATE::EN_HIT2);
			else _thisEn->SetState(EN_STATE::EN_IDLE);
		}
	}
}

void enemyHit::ExitState()
{
	isDown = false;
	_hitIdxTimer = 0;
}
