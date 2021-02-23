#include "stdafx.h"
#include "playerDashAttack.h"

void playerDashAttack::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_dashAttack", true);
	
	//키조작 불가
	_thisPl->setIsControl(false);

	//방향에 따른 공격 렉트 생성
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x - _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE* 0.2, ATTACKSIZE / 2);
		break;
	case DIRECTION::RIGHT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x + _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE*0.2, ATTACKSIZE / 2);
		break;
	}
	
	//공격여부
	if(checkEnemy())_isCollision = true;

	//무기떨어뜨리기
	dropWeapon();
}

void playerDashAttack::UpdateState()
{
	//공격판정 1번
	_thisPl->getInfo().isAttack = false;
	
	//피격에 성공했다면 인덱스번호가 방향에 따라 특정 번호일때 이펙트를 한번만 출력
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_isCollision && _thisPl->getObj().imgIndex.x >= 6)
		{
			SOUND_M->playSFX("kyoko_sAttack");

			EFFECT_M->play("ef_blueAttack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 6)
		{
			EFFECT_M->play("ef_blueAttack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	}

	//프레임이 다 돌면 원래 상태로 돌아가기
	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	//달리는 키를 누르고 있으면 달리는 상태로 돌아가기
	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}
	//이동
	if (_thisPl->getInfo().dest == DIRECTION::LEFT)
		_thisPl->movePos(-_thisPl->getInfo().speed*1.2, 0, 0);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT)
		_thisPl->movePos(_thisPl->getInfo().speed*1.2, 0, 0);
}

void playerDashAttack::ExitState()
{
}
