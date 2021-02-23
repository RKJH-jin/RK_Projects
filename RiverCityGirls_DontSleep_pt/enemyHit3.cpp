#include "stdafx.h"
#include "enemyHit3.h"
#include "Enemy.h"

void enemyHit3::EnterState()
{
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);

	if(_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisEn->getObj()->imgIndex.x = 6;
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		_thisEn->getObj()->imgIndex.x = 2;
	}
	LookAtPlayer();
	_hitIdxTimer = 0;
}

void enemyHit3::UpdateState()
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
		if (_thisEn->getObj()->imgIndex.x == 8)
		{
			_thisEn->SetState(EN_STATE::EN_DOWN);
		}
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		if (_thisEn->getObj()->imgIndex.x == 0)
		{
			_thisEn->SetState(EN_STATE::EN_DOWN);
		}
	}
}

void enemyHit3::ExitState()
{
	_hitIdxTimer = 0;
}
