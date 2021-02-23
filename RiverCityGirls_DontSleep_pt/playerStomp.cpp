#include "stdafx.h"
#include "playerStomp.h"

void playerStomp::EnterState()
{
	//변수초기화
	_isCollision = false;

	//이미지 변경
	_thisPl->changeImg("pl_stomp", true);

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

	//공격여부 체크
	if (checkEnemy())_isCollision = true;

	//무기떨어뜨리기
	dropWeapon();
}

void playerStomp::UpdateState()
{
	//무기판정끗
	_thisPl->getInfo().isAttack = false;

	//피격에 성공했다면 인덱스번호가 방향에 따라 특정 번호일때 이펙트를 한번만 출력
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 6)
		{
			SOUND_M->playSFX("kyoko_stomp");

			EFFECT_M->play("ef_spark", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) *0.6);
			_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_isCollision && _thisPl->getObj().imgIndex.x >= 6)
		{
			
			SOUND_M->playSFX("kyoko_stomp");

			EFFECT_M->play("ef_spark", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom)*0.6);
			_isCollision = false;
		}
		break;
	}
	
	//프레임이 다 돌면 원래 상태로 돌아가기
	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerStomp::ExitState()
{
}
