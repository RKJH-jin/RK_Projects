#include "stdafx.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "StageManager.h"
#include "Player.h"

/*====================================================================
	스테이지 초기화 시 에너미 매니저와 오브젝트 매니저를 할당하고 초기화합니다.
====================================================================*/
HRESULT Stage::init()
{
	_enemyM = new EnemyManager;
	_enemyM->init();
	_enemyM->setLinkStageM(_stageM);

	_objectM = new ObjectManager;
	_objectM->init();

	return S_OK;
}

void Stage::release()
{
	_enemyM->release();
	SAFE_DELETE(_enemyM);

	_objectM->release();
	SAFE_DELETE(_objectM);
}

void Stage::update()
{
	_enemyM->update();
	_objectM->update();


	if (lockEventEnd == false)
	{
		startLocationLock(vector3(_lockStartLine, 0, 0), _stageM->getPlayer()->getObj().pos, _maxEnemyCount);
	}
}

void Stage::render()
{
	/*====================================================================
		배경과 에너미와 오브젝트를 렌더한다.
	====================================================================*/
	backGround->render(getMapDC(), backGround->getWidth() / 2, backGround->getHeight() / 2);
	_enemyM->render();
	_objectM->render();
	wallRender();


	if (_leftDoor.isUsed) _leftDoor.img->render(getMapDC(), (_leftDoor.LT.x + _leftDoor.RT.x) / 2, _leftDoor.LT.z - 200);
	if (_rightDoor.isUsed) _rightDoor.img->render(getMapDC(), (_rightDoor.LT.x + _rightDoor.RT.x) / 2, _rightDoor.LT.z - 200);
	if (_shopDoor.isUsed) _shopDoor.img->render(getMapDC(), (_shopDoor.LT.x + _shopDoor.RT.x) / 2, _shopDoor.LT.z - 200);
}

void Stage::backWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	tagWall temp;
	temp.LT = lt;
	temp.RT = rt;
	temp.RB = rb;
	temp.LB = lb;
	_vBackWall.push_back(temp);
}

void Stage::leftWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	tagWall temp;
	temp.LT = lt;
	temp.RT = rt;
	temp.RB = rb;
	temp.LB = lb;
	_vLeftWall.push_back(temp);
}

void Stage::rightWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	tagWall temp;
	temp.LT = lt;
	temp.RT = rt;
	temp.RB = rb;
	temp.LB = lb;
	_vRightWall.push_back(temp);
}

void Stage::floorInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	_floor.LT = lt;
	_floor.RT = rt;
	_floor.RB = rb;
	_floor.LB = lb;
}

void Stage::poolInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb)
{
	_pool.LT = lt;
	_pool.RT = rt;
	_pool.RB = rb;
	_pool.LB = lb;
}

void Stage::startLocationLock(vector3 lockPos, vector3 playerPos, int maxEnemyNum)
{
	if (lockEventStart == false && lockPos.x < playerPos.x)
	{
		EVENT_M->addEvent(new locationLock(), true); // 이벤트 시작
		_doorActive = DOOR_ACTIVITY::NON_ACTIVE;
		lockEventStart = true;
		_enemyCount = 0;
		_maxEnemyCount = maxEnemyNum;
		_leftDoor.img = IMG_M->findImage("UI_Locked_Door");
		_rightDoor.img = IMG_M->findImage("UI_Locked_Door");
		_shopDoor.img = IMG_M->findImage("UI_Locked_Door");
	}

	if (lockEventStart == true && lockEventEnd == false)
	{
		if (_enemyCount >= _maxEnemyCount && ((LocationLock*)UI_M->findUI("LocationLock"))->isUnlockStart() == false)
		{
			((LocationLock*)UI_M->findUI("LocationLock"))->startUnlock();
		}
		if (((LocationLock*)UI_M->findUI("LocationLock"))->isUnlockEnd())
		{
			_doorActive = DOOR_ACTIVITY::ACTIVE;

			((LocationLock*)UI_M->findUI("LocationLock"))->setActive(false);
			_leftDoor.img = IMG_M->findImage("UI_UnLocked_Door");
			_rightDoor.img = IMG_M->findImage("UI_UnLocked_Door");
			_shopDoor.img = IMG_M->findImage("UI_Shop_Door1");
			lockEventEnd = true;
		}
	}
}

void Stage::polylineRender(vector3 A, vector3 B)
{
	POINT temp[2];
	temp[0] = PointMake(A.x, A.z);
	temp[1] = PointMake(B.x, B.z);
	Polyline(getMapDC(), temp, 2);
}

void Stage::wallRender()
{
	if (KEY_M->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < _vBackWall.size(); ++i)
		{
			polylineRender(_vBackWall[i].LT, _vBackWall[i].RT);
			polylineRender(_vBackWall[i].RT, _vBackWall[i].RB);
			polylineRender(_vBackWall[i].RB, _vBackWall[i].LB);
			polylineRender(_vBackWall[i].LB, _vBackWall[i].LT);
		}

		for (int i = 0; i < _vLeftWall.size(); ++i)
		{
			polylineRender(_vLeftWall[i].LT, _vLeftWall[i].RT);
			polylineRender(_vLeftWall[i].RT, _vLeftWall[i].RB);
			polylineRender(_vLeftWall[i].RB, _vLeftWall[i].LB);
			polylineRender(_vLeftWall[i].LB, _vLeftWall[i].LT);
		}

		for (int i = 0; i < _vRightWall.size(); ++i)
		{
			polylineRender(_vRightWall[i].LT, _vRightWall[i].RT);
			polylineRender(_vRightWall[i].RT, _vRightWall[i].RB);
			polylineRender(_vRightWall[i].RB, _vRightWall[i].LB);
			polylineRender(_vRightWall[i].LB, _vRightWall[i].LT);
		}

		polylineRender(_pool.LT, _pool.RT);
		polylineRender(_pool.RT, _pool.RB);
		polylineRender(_pool.RB, _pool.LB);
		polylineRender(_pool.LB, _pool.LT);

		polylineRender(_floor.LB, _floor.RB);

		polylineRender(_leftDoor.LT, _leftDoor.RT);
		polylineRender(_leftDoor.RT, _leftDoor.RB);
		polylineRender(_leftDoor.RB, _leftDoor.LB);
		polylineRender(_leftDoor.LB, _leftDoor.LT);

		polylineRender(_rightDoor.LT, _rightDoor.RT);
		polylineRender(_rightDoor.RT, _rightDoor.RB);
		polylineRender(_rightDoor.RB, _rightDoor.LB);
		polylineRender(_rightDoor.LB, _rightDoor.LT);
	}
}
