#include "stdafx.h"
#include "IPlayerState.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Weapon.h"

//업데이트 일시정지 유무 
bool IPlayerState::pauseUpdate()
{
	//키조작이 불가능일경우 
	if (!_thisPl->getInfo().isControl) return true;

	//그외
	else return false;
}

//프레임 실행여부
bool IPlayerState::isEndFrame(bool reverse)
{
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
	{
		//현재 프레임번호가 끝번호면 프레임재생이 끝
		if (reverse == false && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())
			return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() <= 0)
			return true;

		return false;
	}
	case DIRECTION::RIGHT:
	{
		//현재 프레임번호가 0 번호면 프레임재생이 끝
		if (reverse == false && _thisPl->getObj().img->getFrameX() <= 0) return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())return true;
		return false;
	}
	}
}

//무기 떨어뜨리기
void IPlayerState::dropWeapon()
{
	//무기를 들고 있다면 떨어뜨리기
	if (_thisPl->getInfo().hasWeapon)
	{
		//무기를 떨어뜨림.
		_thisPl->getInfo().hasWeapon = false;
		//무기의 떨어질 초기위치 설정
		_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
		_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
		_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;

		//무기 렌더 활성화
		_thisPl->getInfo().attackObj->isRender = true;

		//무기가 향할 골 설정
		_thisPl->getInfo().attackGoal.x = _thisPl->getObj().pos.x;
		if (_thisPl->getInfo().attackGoal.x > CAMERA_M->GetMapXSize())_thisPl->getInfo().attackGoal.x = CAMERA_M->GetMapXSize();
		_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y - 100;
		_thisPl->getInfo().attackGoal.z = _thisPl->getObj().pos.z;
		_thisPl->getInfo().attackGoal.y = _thisPl->getObj().pos.y - 100;
		_thisPl->getInfo().goalState = GOALPOS::WINOUT;
	}

}

void IPlayerState::walkPattern()
{
	//걷기
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
}

void IPlayerState::basePattern()
{
	//걷기
	walkPattern();

	//가드
	if (KEY_M->isStayKeyDown('F'))_thisPl->setState(PL_STATE::GUARD);

	//약공격
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO1);

}

bool IPlayerState::checkWeapon()
{
	RECT temp;
	for (int i = 0; i != _thisPl->getObjectM()->getVObject().size(); i++)
	{
		if (_thisPl->getObjectM()->getVObject()[i]->getObj()->group != OBJECT_GROUP::WEAPON) continue;

		if (!_thisPl->getObjectM()->getVObject()[i]->getObj()->isRender) continue;

		if (IntersectRect(&temp, &_thisPl->getRefObj().rc,
			&(_thisPl->getObjectM()->getVObject()[i]->getObj()->rc))
			&& _thisPl->isRange(*_thisPl->getObjectM()->getVObject()[i]->getObj()))
		{
			_thisPl->getObjectM()->popObject(i);
			Object* weapon = new Weapon(WEAPON_TYPE::BAT, vector3(0,0,0));
			_thisPl->getInfo().attackObj = weapon->getObj();
			_thisPl->getInfo().attackObj->isRender = false;
			return true;
		}
	}
	return false;
}

//공격상태면 공격으로 전환
bool IPlayerState::checkEnemy()
{
	RECT temp;
	//인터섹트렉트랑 / isrange함수로 같은 줄. 비슷한 범위의 z값에있는지 확인함.
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (_thisPl->getEnemyM()->getVEnemy()[i]->getInfo().isAttack)return false;

		if (IntersectRect(&temp, &_thisPl->getInfo().attackRc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& _thisPl->isRange(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj()))
		{
			_thisPl->getInfo().isAttack = true;
			return _thisPl->getInfo().isAttack;
		}
	}
	return false;
}

//강공격
void IPlayerState::sAttack()
{
	if (KEY_M->isOnceKeyDownV('D')) _thisPl->setState(PL_STATE::SATTACK);
	//_thisPl->setState(PL_STATE::HIT);
	{
		//for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
		//{
		//	//if (_thisPl->getEnemyM()->getVEnemy()[i]);
		//	_thisPl->setState(PL_STATE::SATTACK);
		//	//★ 적상태가 쓰러진상태면 스톰프로 동작바꾸기
		//	//if (_thisPl->getEnemyM()->getVEnemy()[i]);
		//}
	}
}

//상하이동
void IPlayerState::lineMove(float speed)
{	
	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -speed, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, speed, 0);
}

//좌우이동
void IPlayerState::crossMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-speed, 0, 0);
}

void IPlayerState::ladderMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_UP))
	{
		_thisPl->movePos(0, 0, speed);
	}


	if (KEY_M->isStayKeyDown(VK_DOWN))
	{
		_thisPl->movePos(0, 0, -speed);
	}
}
