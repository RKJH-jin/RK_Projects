#include "stdafx.h"
#include "playerThrow.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "Weapon.h"

void playerThrow::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_wBatThrow", false);

	_isCollision = false;

	_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
	_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
	_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;

	_thisPl->getInfo().attackObj->isRender = true;

	//무기가 향할 골 설정/이미지 설정
	if (_thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->getInfo().attackObj->imgIndex.y = 1;
		_thisPl->getInfo().attackGoal.x = _thisPl->getObj().pos.x + WINSIZEX / 2;
		if (_thisPl->getInfo().attackGoal.x > CAMERA_M->GetMapXSize())_thisPl->getInfo().attackGoal.x = CAMERA_M->GetMapXSize();
	}

	if (_thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->getInfo().attackObj->imgIndex.y = 0;
		_thisPl->getInfo().attackGoal.x = _thisPl->getObj().pos.x - WINSIZEX / 2;
		if (_thisPl->getInfo().attackGoal.x < 0)_thisPl->getInfo().attackGoal.x = 0;
	}
	_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y - 100;
	_thisPl->getInfo().attackGoal.z = _thisPl->getObj().pos.z;
	_thisPl->getInfo().attackGoal.y = _thisPl->getObj().pos.y - 100;
	_thisPl->getInfo().goalState = GOALPOS::WINOUT;


}

void playerThrow::UpdateState()
{
	//공격 렉트를 어택 오브젝트의 위치에 맞춤.
	_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getInfo().attackObj->pos.x,
		_thisPl->getInfo().attackObj->pos.z + _thisPl->getInfo().attackObj->pos.y,
		_thisPl->getInfo().attackObj->size.x + 200, _thisPl->getInfo().attackObj->size.z + 100);

	RECT _temp;
	//공격 판정
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (//_thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj(), 40)&&
			 IntersectRect(&_temp, &_thisPl->getInfo().attackRc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{
			_thisPl->getInfo().isAttack = true;
		}
	}

	//방향에따라 무기 없는 순간을 체크
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_thisPl->getInfo().dest == DIRECTION::LEFT
			&& _thisPl->getObj().imgIndex.x >= 2)
			_thisPl->getInfo().hasWeapon = false;
		break;
	case DIRECTION::RIGHT:
		if (_thisPl->getInfo().dest == DIRECTION::RIGHT
			 && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 2)
			_thisPl->getInfo().hasWeapon = false;
		break;
	}

	if (isEndFrame(false))
	{
		//키조작 가능한 상태로 변경
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerThrow::ExitState()
{
}
