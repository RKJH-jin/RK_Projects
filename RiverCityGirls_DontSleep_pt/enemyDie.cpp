#include "stdafx.h"
#include "enemyDie.h"
#include "Enemy.h"
#include "ObjectManager.h"

void enemyDie::EnterState()
{
	SOUND_M->playSFX("enemy_die");
	_thisEn->SetImage();
	_money = true;
	_checkTimer = TIME_M->getWorldTime();
	_thisEn->getObjectM()->pushItem(ITEM_TYPE::COIN, vector3(_thisEn->getObj()->pos.x, 0.0f, _thisEn->getObj()->pos.z - 10));
	_thisEn->getObjectM()->pushItem(ITEM_TYPE::MONEY, vector3(_thisEn->getObj()->pos.x, 0.0f, _thisEn->getObj()->pos.z + 50));
}

void enemyDie::UpdateState()
{
	if(_thisEn->getObj()->alpha > 5) _thisEn->getObj()->alpha -= 5;
	if (endFrame()) _thisEn->getInfo().isDead = true;
	if (TIME_M->getWorldTime() - _checkTimer >= 3)
	{
		_money = false;
	}

}

void enemyDie::ExitState()
{
}
