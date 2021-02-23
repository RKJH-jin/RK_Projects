#include "stdafx.h"
#include "enemyWRun.h"
#include "Enemy.h"

void enemyWRun::EnterState()
{
	SOUND_M->playSFX("enemy_run");
	_thisEn->getInfo().speed = _thisEn->getInfo().baseSpeed + 3;
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
	//방향에 따른 이팩트 실행
	switch (_thisEn->getInfo().dest)
	{
	case DIRECTION::LEFT:
		EFFECT_M->play("ef_runL", _thisEn->getObj()->rc.right, _thisEn->getObj()->rc.bottom);
		break;
	case DIRECTION::RIGHT:
		EFFECT_M->play("ef_runR", _thisEn->getObj()->rc.left, _thisEn->getObj()->rc.bottom);
		break;
	}
}

void enemyWRun::UpdateState()
{
	_checkTimer += TIME_M->getElapsedTime();
	if (_checkTimer > 1.0f)
	{
		_tempPos = _thisEn->getObj()->pos;
	}

	Jump();

	if (_tempPos == _thisEn->getObj()->pos)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) > 250)
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
		if (_checkTimer > 4.0f)
		{
			_checkTimer = 0;
		}
	}
	else
	{
		_thisEn->getObj()->obstacle = nullptr;
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

void enemyWRun::ExitState()
{
	_thisEn->getInfo().speed = _thisEn->getInfo().baseSpeed;
}
