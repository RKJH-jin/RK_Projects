#include "stdafx.h"
#include "cheerLeader.h"
#include "Player.h"

HRESULT cheerLeader::init()
{

	Enemy::init();

	_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolCheerIdle"), _obj.pos);
	_ENEMY_TYPE = ENEMY_TYPE::CHEERLEADER;
	SetState(EN_STATE::EN_IDLE);


	return S_OK;
}

void cheerLeader::release()
{
}

void cheerLeader::update()
{
	Enemy::update();
}
