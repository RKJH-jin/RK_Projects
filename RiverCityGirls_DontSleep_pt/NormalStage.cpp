#include "stdafx.h"
#include "NormalStage.h"

HRESULT NormalStage::init()
{
	Stage::init();

	/*====================================================================
		스테이지의 배경 이미지를 설정하고, 카메라에게 맵 사이즈를 알려 줍니다.
	====================================================================*/
	backGround = IMG_M->findImage("normalStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		스테이지의 벽을 배치합니다. LT, RT, RB, LB 순!!
	====================================================================*/
	backWallInit(vector3(260, WINSIZEY, 0), vector3(932, WINSIZEY, 0), vector3(932, 0, 500), vector3(260, 0, 500));
	backWallInit(vector3(980, WINSIZEY, 0), vector3(1640, WINSIZEY, 0), vector3(1640, 0, 550), vector3(980, 0, 550));
	backWallInit(vector3(1745, WINSIZEY, 0), vector3(2500, WINSIZEY, 0), vector3(2500, 0, 445), vector3(1745, 0, 445));

	leftWallInit(vector3(0, WINSIZEY, 0), vector3(260, WINSIZEY, 0), vector3(260, 0, 500), vector3(0, 0, 760));
	leftWallInit(vector3(1640, WINSIZEY, 0), vector3(1745, WINSIZEY, 0), vector3(1745, 0, 445), vector3(1640, 0, 550));

	rightWallInit(vector3(932, WINSIZEY, 0), vector3(980, WINSIZEY, 0), vector3(980, 0, 550), vector3(932, 0, 500));
	rightWallInit(vector3(2500, WINSIZEY, 0), vector3(2865, WINSIZEY, 0), vector3(2865, 0, 795), vector3(2500, 0, 445));

	floorInit(vector3(0, 0, 760), vector3(2865, 0, 795), vector3(2865, 0, 837), vector3(0, 0, 837));
	/*====================================================================
	배경음악을 넣어줍니다.
	====================================================================*/
	SOUND_M->playMusic("hardStageBG");
	/*====================================================================
		오브젝트와 에너미를 배치합니다.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(440, 0, 755));
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(1000, 0, 850));
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(1650, 0, 830));
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(2300, 0, 750));
	_objectM->pushObject(OBJECT_TYPE::VENDINGMACHINE, vector3(2400, 0, 500));



	_objectM->pushItem(ITEM_TYPE::MEAT, vector3(WINSIZEX / 3 * 2, 0, WINSIZEY / 2));
	_objectM->pushWeapon(WEAPON_TYPE::BAT, vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 250));

	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 2 - 200, 0, WINSIZEY / 2 + 300));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 2 + 200, 0, WINSIZEY / 2 + 200));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 2 + 400, 0, WINSIZEY / 2 + 300));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLBOY, vector3(WINSIZEX / 2 + 600, 0, WINSIZEY / 2 + 200));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLBOY, vector3(WINSIZEX / 2 + 800, 0, WINSIZEY / 2 + 300));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLBOY, vector3(WINSIZEX / 2 + 1000, 0, WINSIZEY / 2 + 250));



	/*====================================================================
		스테이지 진입 시 실행 될 이벤트를 추가합니다.
	====================================================================*/

	// 지역락 관련 변수들
	_enemyCount = 0;
	_maxEnemyCount = 1;
	lockEventStart = lockEventEnd = false;
	_lockStartLine = 1200;


	/*====================================================================
		스테이지에 문을 추가합니다
	====================================================================*/
	_doorActive = DOOR_ACTIVITY::NON_ACTIVE;
	_leftDoor.isUsed = true;
	_leftDoor.LT = vector3(0, 0, 610);
	_leftDoor.RT = vector3(180, 0, 610);
	_leftDoor.LB = vector3(0, 0, 775);
	_leftDoor.RB = vector3(180, 0, 775);
	_leftDoor.img = IMG_M->findImage("UI_UnLocked_Door");

	_rightDoor.isUsed = true;
	_rightDoor.LT = vector3(2580, 0, 535);
	_rightDoor.RT = vector3(2820, 0, 535);
	_rightDoor.LB = vector3(2580, 0, 760);
	_rightDoor.RB = vector3(2820, 0, 760);
	_rightDoor.img = IMG_M->findImage("UI_UnLocked_Door");

	_shopDoor.isUsed = true;
	_shopDoor.LT = vector3(1070, 0, 540);
	_shopDoor.RT = vector3(1270, 0, 540);
	_shopDoor.LB = vector3(1070, 0, 600);
	_shopDoor.RB = vector3(1270, 0, 600);
	_shopDoor.img = IMG_M->findImage("UI_Shop_Door1");


	return S_OK;
}

void NormalStage::release()
{
	Stage::release();
}

void NormalStage::update()
{
	Stage::update();
}

void NormalStage::render()
{
	Stage::render();
}
