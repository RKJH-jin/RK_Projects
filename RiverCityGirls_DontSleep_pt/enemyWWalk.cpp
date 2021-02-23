#include "stdafx.h"
#include "enemyWWalk.h"
#include "Enemy.h"

void enemyWWalk::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyWWalk::UpdateState()
{
	_checkTimer += TIME_M->getElapsedTime();
	if (_checkTimer > 1.0f)
	{
		_tempPos = _thisEn->getObj()->pos;
	}

	Jump();
	if (_tempPos == _thisEn->getObj()->pos)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) > 150)
		{
			LookAtPlayer();
		}

		if (_thisEn->getObj()->obstacle != nullptr)
		{
			if (fabs(_thisEn->getObj()->obstacle->bottomPlane[0].getStart().z - _thisEn->getPlayerAddress()->getObj().pos.z) >=
				fabs(_thisEn->getObj()->obstacle->bottomPlane[2].getStart().z - _thisEn->getPlayerAddress()->getObj().pos.z))
			{
				_thisEn->xzyMove(0, _thisEn->getInfo().speed, 0);
			}
			else
			{
				_thisEn->xzyMove(0, -_thisEn->getInfo().speed, 0);
			}
		}

		if (_thisEn->getInfo().dest == DIRECTION::LEFT)
		{
			_thisEn->xzyMove(-_thisEn->getInfo().speed, 0, 0);
		}
		else if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisEn->xzyMove(_thisEn->getInfo().speed, 0, 0);
		}
		if (_checkTimer > 3.0f)
		{
			_checkTimer = 0;
		}
	}
	else
	{
		LookAtPlayer();

		tempAngle = getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z);
		if (abs(_thisEn->getPlayerAddress()->getObj().pos.x - _thisEn->getObj()->pos.x) >= 90)
		{
			_thisEn->xzyMove(cosf(-tempAngle) * _thisEn->getInfo().speed, -sinf(tempAngle) * 0, 0);
		}

		if (abs(_thisEn->getPlayerAddress()->getObj().pos.z - _thisEn->getObj()->pos.z) >= 0)
		{
			_thisEn->xzyMove(cosf(tempAngle) * 0, -sinf(tempAngle) * _thisEn->getInfo().speed, 0);
		}

	}
	//충분히 가까워졌으면 IDLE로 돌아간다.
	if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
	{
		_thisEn->SetState(EN_STATE::EN_WIDLE);
	}
}

void enemyWWalk::ExitState()
{
}
