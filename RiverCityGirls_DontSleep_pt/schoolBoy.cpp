#include "stdafx.h"
#include "schoolBoy.h"
#include "Player.h"
#include "StageManager.h"



HRESULT schoolBoy::init()
{
	Enemy::init();
	_ENEMY_TYPE = ENEMY_TYPE::SCHOOLBOY;
	if (_stageM->getCurStage() == STAGETYPE::EASY)
	{
		_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolBoyIdle"), _obj.pos);
		SetState(EN_STATE::EN_IDLE);
	}
	else if (_stageM->getCurStage() == STAGETYPE::NORMAL)
	{
		switch (RND->getInt(2))
		{
		case 0:
			_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolBoyWIdle"), _obj.pos);
			SetState(EN_STATE::EN_WIDLE);
			break;
		case 1:
			_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolBoyIdle"), _obj.pos);
			SetState(EN_STATE::EN_IDLE);
			break;
		}
	}
	else if (_stageM->getCurStage() == STAGETYPE::HARD)
	{
		_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolBoyWIdle"), _obj.pos);
		SetState(EN_STATE::EN_WIDLE);
	}
	return S_OK;
}

void schoolBoy::release()
{
}

void schoolBoy::update()
{
	Enemy::update();
}
