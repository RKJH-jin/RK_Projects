#include "stdafx.h"
#include "playerIdle.h"
#include "Enemy.h"
#include "EnemyManager.h"

void playerIdle::EnterState()
{
	//이미지 변경
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatIdle", true);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}

	}
	else _thisPl->changeImg("pl_idle", true);

	//방향조작이 가능한 상태로 변경
	_thisPl->getInfo().isConDest = true;
	//공격 상태 아님
	_thisPl->getInfo().isAttack = false;
	//타이머를 월드타이머로 맞춰서 초기화
	_stateTimer = TIME_M->getWorldTime();

	//키커맨더 벡터 비움
	KEY_M->clearVKey();

	//맞지않은상태로변경
	
}

void playerIdle::UpdateState()
{
	//일정시간동안 움직임이 없으면 기다림 상태로 전환
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)_thisPl->setState(PL_STATE::WAIT);
	//업데이트 정지 유무
	if (pauseUpdate())return;

	//기본 동작
	basePattern();
	
	//강공격
	sAttack();

	//줍기
	if (KEY_M->isOnceKeyDownV('E')) { _thisPl->setState(PL_STATE::PICK); }
	
	//동료되기

	RECT temp;
	//인터섹트렉트랑 / isrange함수로 같은 줄. 비슷한 범위의 z값에있는지 확인함.

	//동료가 없는 상태에서 빌고있는 에너미랑 충돌하면
	if(!_thisPl->getInfo().hasMember)
	{
		for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
		{
			if(_thisPl->getEnemyM()->getVEnemy()[i]->getState() ==EN_STATE::EN_BEGGING)
			{
				if (IntersectRect(&temp, &_thisPl->getRefObj().rc,
					&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
					&& _thisPl->isRange(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj()))
				{
					_thisPl->setState(PL_STATE::GRAB);
				}
			}
		}
	}
	if (KEY_M->isOnceKeyDownV('Q')) 
	{
		_thisPl->setState(PL_STATE::PICK); 
	}

}

void playerIdle::ExitState()
{
}
