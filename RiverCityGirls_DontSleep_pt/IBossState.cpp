#include "stdafx.h"
#include "IBossState.h"
#include "Boss.h"

void IBossState::LookatPlayer()
{
	if (_thisBs->getPlayerAddress()->getObj().pos.x < _thisBs->getObj()->pos.x)
	{
		_thisBs->getInfo().dest = DIRECTION::LEFT;
	}
	else if (_thisBs->getPlayerAddress()->getObj().pos.x > _thisBs->getObj()->pos.x)
	{
		_thisBs->getInfo().dest = DIRECTION::RIGHT;
	}
}

void IBossState::ResetFrame()
{
	if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}
	else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void IBossState::Damaged(int atk)
{
	_thisBs->getInfo().hp -= atk;

	if (_thisBs->getInfo().hp < 0) { _thisBs->getInfo().hp = 0; }

	//체력이 0이면 죽는다.
	if (_thisBs->getInfo().hp <= 0)
	{
		_thisBs->SetState(BS_STATE::DEATH);
	}
	//체력이 1/3 이하면 페이즈
	else if (_thisBs->getInfo().hp <= _thisBs->getInfo().maxHp / 3 && _thisBs->getPhaseCount() == 0)
	{
		_thisBs->SetState(BS_STATE::PHASE);
		_thisBs->getPhaseCount()++;
	}
	//체력이 1/2 이하면 그로기
	else if (_thisBs->getInfo().hp <= _thisBs->getInfo().maxHp / 2 && _thisBs->getGroggyCount() == 0)
	{
		_thisBs->SetState(BS_STATE::GROGGY);
		_thisBs->getGroggyCount()++;
	}
	else _thisBs->SetState(BS_STATE::ATTACKED);
}

void IBossState::Attack()
{
	if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->rc.right, _thisBs->getObj()->rc.top, 100, 200);
	}
	else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
	{
		_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->rc.left - 100, _thisBs->getObj()->rc.top, 100, 200);
	}
	_thisBs->getInfo().isAttack = true;
}

void IBossState::collision()
{
	RECT _temp;
	if (IntersectRect(&_temp, &_thisBs->getInfo().rcAttack, &_thisBs->getPlayerAddress()->getRefObj().rc) && fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30);
}
