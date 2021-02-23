#include "stdafx.h"
#include "EnemyManager.h"

#include "Stage.h"
#include "StageManager.h"
#include "schoolGirl.h"
#include "schoolBoy.h"
#include "cheerLeader.h"
#include "Boss.h"

HRESULT EnemyManager::init()
{
	return S_OK;
}

void EnemyManager::release()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->release();
		delete _vEnemy[i];
	}
	_vEnemy.clear();
}

void EnemyManager::update()
{
	for (int i = 0; i < _vEnemy.size();)
	{
		_vEnemy[i]->update();

		if (_vEnemy[i]->getInfo().isDead)
		{ 
			popEnemy(i);
		}
		else  i++;
	}

	
}

void EnemyManager::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		ZORDER_M->renderObject(getMapDC(), _vEnemy[i]->getObj(), RENDERTYPE::FRAME_RENDER);
		_vEnemy[i]->render();
	}	
}

void EnemyManager::pushEnemy(ENEMY_TYPE type, vector3 pos)
{
	Enemy* _enemy = new Enemy;
	switch (type)
	{
	case ENEMY_TYPE::SCHOOLGIRL:
		_enemy = new schoolGirl;
		break;
	case ENEMY_TYPE::SCHOOLBOY:
		_enemy = new schoolBoy;
		break;
	case ENEMY_TYPE::CHEERLEADER:
		_enemy = new cheerLeader;
		break;
	case ENEMY_TYPE::BOSS:
		_enemy = new Boss;
		break;
	}
	
	_enemy->setLinkStageM(_stageM);
	_enemy->setPosition(pos);
	_enemy->init();
	_vEnemy.push_back(_enemy);
}

void EnemyManager::popEnemy(int index)
{
	for (int i = 0; i < _vEnemy.size();)
	{
		if (i == index)
		{
			SAFE_DELETE(_vEnemy[i]);
			_vEnemy.erase(_vEnemy.begin() + i);
			_stageM->getStage()->setEnemyCount(_stageM->getStage()->getEnemyCount() + 1);
			break;
		}
		else  i++;
	}
}
