#include "stdafx.h"
#include "enemyBegging.h"
#include "Enemy.h"

void enemyBegging::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyBegging::UpdateState()
{
	cout << _thisEn->getObj()->imgIndex.x << endl;
	LookAtPlayer();
	if(!EFFECT_M->getIsrunning("ef_beg")) EFFECT_M->play("ef_beg", (_thisEn->getRefObj().rc.left + _thisEn->getRefObj().rc.right) / 2, _thisEn->getRefObj().rc.top);
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x > _thisEn->getObj()->img->getMaxFrameX())
	{
		_thisEn->getObj()->imgIndex.x = 1;
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x < 0)
	{
		_thisEn->getObj()->imgIndex.x = 1;
	}
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyBegging::ExitState()
{
}
