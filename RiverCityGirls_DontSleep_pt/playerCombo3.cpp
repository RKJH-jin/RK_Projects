#include "stdafx.h"
#include "playerCombo3.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo3::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_comboAttack3", false);

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

	//공격여부: 피격에 성공했는지 확인
	if (checkEnemy()) _isCollision = true;
}

void playerCombo3::UpdateState()
{
	RECT _temp;

	//한번만 피격
	_thisPl->getInfo().isAttack = false;

	//피격에 성공했다면 인덱스번호가 방향에 따라 특정 번호일때 이펙트를 한번만 출력
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_isCollision && _thisPl->getObj().imgIndex.x >= 5)
		{
			SOUND_M->playSFX("kyoko_combo");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
			(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
		_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() -5)
		{
			SOUND_M->playSFX("kyoko_combo");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
			(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
		_isCollision = false;
		}
		break;
	}

	//인덱스가 다 돌아가면 일반동작으로
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	//걷기
	walkPattern();
}

void playerCombo3::ExitState()
{
}
