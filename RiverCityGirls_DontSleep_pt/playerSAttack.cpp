#include "stdafx.h"
#include "playerSAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerSAttack::EnterState()
{
	RECT temp;
	//몹이 넘어져있으면 밟기로 변경
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		
		if (IntersectRect(&temp, &_thisPl->getRefObj().rc,&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{
			if(_thisPl->getEnemyM()->getVEnemy()[i]->getState() == EN_STATE::EN_DOWN
			 || _thisPl->getEnemyM()->getVEnemy()[i]->getState() == EN_STATE::EN_WEAPONHIT)
			{
				_thisPl->setState(PL_STATE::STOMP);
				return;
			}
		}
	}

	
	//무기든 상태면 던지기로 상태변경
	if (_thisPl->getInfo().hasWeapon) _thisPl->setState(PL_STATE::THROW);

	//무기를 들고 있지 않으면 이미지 변경
	else _thisPl->changeImg("pl_sAttack", false);
	
	
	
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
			ATTACKSIZE* 0.2, ATTACKSIZE / 2);
		break;
	}

	//키입력 막음
	_thisPl->setIsControl(false);

	//공격여부: 피격에 성공했는지 확인
	if (checkEnemy()) _isCollision = true;
}

void playerSAttack::UpdateState()
{
	//한번만 피격
	_thisPl->getInfo().isAttack = false;

	//피격에 성공했다면 인덱스번호가 방향에 따라 특정 번호일때 이펙트를 한번만 출력
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_thisPl->getInfo().dest == DIRECTION::LEFT
			&&_isCollision && _thisPl->getObj().imgIndex.x >= 6)
		{
			SOUND_M->playSFX("kyoko_sAttack");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_thisPl->getInfo().dest == DIRECTION::RIGHT
			&&_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 6)
		{
			SOUND_M->playSFX("kyoko_sAttack");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	}

	//프레임이 끝나면
	if (isEndFrame(false))
	{
		//키조작 가능한 상태로 변경
		_thisPl->setIsControl(true);
		//일반 동작으로 변경
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttack::ExitState()
{
}
