#include "stdafx.h"
#include "enemyHit2.h"
#include "Enemy.h"

void enemyHit2::EnterState()
{
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);

	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisEn->getObj()->imgIndex.x = 3;
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		_thisEn->getObj()->imgIndex.x = 5;
	}
	LookAtPlayer();
	_hitIdxTimer = 0;
}

void enemyHit2::UpdateState()
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
		if (_thisEn->getObj()->imgIndex.x == 5)
		{
			_thisEn->SetState(EN_STATE::EN_IDLE);
		}
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		if (_thisEn->getObj()->imgIndex.x == 3)
		{
			_thisEn->SetState(EN_STATE::EN_IDLE);
		}
	}
}

void enemyHit2::ExitState()
{
	isDown = false;
	_hitIdxTimer = 0;
}
