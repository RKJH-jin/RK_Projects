#include "stdafx.h"
#include "enemyWIdle.h"
#include "Enemy.h"

void enemyWIdle::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
	wait = RND->getInt(2);
	if (_thisEn->getInfo().isActive)
	{
		EFFECT_M->play("ef_point", (_thisEn->getRefObj().rc.left + _thisEn->getRefObj().rc.right) / 2, _thisEn->getRefObj().rc.top);
	}
}

void enemyWIdle::UpdateState()
{
	//플레이어가 오른쪽에 있으면 오른쪽 방향을 본다. 반대면 왼쪽을 본다.
	LookAtPlayer();

	//플레이어가 나보다 높이 있고 공중이 아니면 점프를 한다
	Jump();
	if ((wait && TIME_M->getWorldTime() - _stateTimer > 2.f) || !wait) //대기를 2초 이상 하면
	{
		//내가 동료가 아니고 가까우면 공격한다.
		if (!_thisEn->getInfo().isFriend &&
			getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_WATTACK);
		}
		else
		{
			//가깝지 않으면 다가간다.
			if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 200)
			{
				_thisEn->SetState(EN_STATE::EN_WWALK);
			}
			else
			{
				switch (RND->getInt(2))
				{
				case 0:
					_thisEn->SetState(EN_STATE::EN_WWALK);
					break;
				case 1:
					_thisEn->SetState(EN_STATE::EN_WRUN);
					break;
				}
			}
		}
	}
}

void enemyWIdle::ExitState()
{
	_thisEn->getInfo().isActive = false;
}
