#include "stdafx.h"
#include "EasyStage.h"

HRESULT EasyStage::init()
{
	Stage::init();

	/*====================================================================
		스테이지의 배경 이미지를 설정하고, 카메라에게 맵 사이즈를 알려 줍니다.
	====================================================================*/
	backGround = IMG_M->findImage("easyStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		스테이지의 벽을 배치합니다. LT, RT, RB, LB 순!!
	====================================================================*/
	backWallInit(vector3(350, WINSIZEY, 0), vector3(1635, WINSIZEY, 0), vector3(1635, 0, 385), vector3(350, 0, 385));

	leftWallInit(vector3(57, WINSIZEY, 0), vector3(350, WINSIZEY, 0), vector3(350, 0, 385), vector3(57, 0, 678));

	rightWallInit(vector3(1635, WINSIZEY, 0), vector3(1928, WINSIZEY, 0), vector3(1928, 0, 678), vector3(1635, 0, 385));

	floorInit(vector3(0, 0, 650), vector3(2028, 0, 650), vector3(1928, 0, 650), vector3(57, 0, 650));
	
	/*====================================================================
		배경음악을 넣어줍니다.
	====================================================================*/
	SOUND_M->playSFX("kyoko_battlestart");

	/*====================================================================
		오브젝트와 에너미를 배치합니다.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(440, 0, 545));
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(690, 0, 545));
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(950, 0, 545));
	_objectM->pushObject(OBJECT_TYPE::DESK, vector3(1210, 0, 545));

	_objectM->pushItem(ITEM_TYPE::MEAT, vector3(WINSIZEX / 3 * 2, 0, WINSIZEY * 0.8));
	_objectM->pushItem(ITEM_TYPE::MEAT, vector3(WINSIZEX / 3 * 2+40, 0, WINSIZEY * 0.8));
	_objectM->pushItem(ITEM_TYPE::MEAT, vector3(WINSIZEX / 3 * 2 +80, 0, WINSIZEY * 0.8));
	_objectM->pushWeapon(WEAPON_TYPE::BAT, vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 250));
	
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 2 + 600, 0, WINSIZEY / 2+ 300 ));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLGIRL, vector3(WINSIZEX / 2 + 1000, 0, WINSIZEY / 2 + 300));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLBOY, vector3(WINSIZEX / 2 + 800, 0, WINSIZEY / 2 + 200));
	_enemyM->pushEnemy(ENEMY_TYPE::SCHOOLBOY, vector3(WINSIZEX / 2 + 900, 0, WINSIZEY / 2 + 120));

	/*====================================================================
		스테이지 진입 시 실행 될 이벤트를 추가합니다.
	====================================================================*/
	EVENT_M->addEvent(new cameraMove(vector3(50, 0, 0), 8, 1.5, 0.01f));
	EVENT_M->addEvent(new waitForSec(2.0f));
	EVENT_M->addEvent(new cameraMove(vector3(300, 0, 0), 8, 1.0, 0.01f));
	EVENT_M->addEvent(new waitForSec(2.0f));

	EVENT_M->addEvent(new cameraMove(vector3(50, 0, 0), 8, 1.0, 0.1f));
	EVENT_M->addEvent(new waitForSec(3.5f));
	
	EVENT_M->addEvent(new dialogue(DIALOGLIST::EASY_START), false);


	// 지역락 관련 변수들
	_enemyCount = 0;
	_maxEnemyCount = 1;
	lockEventStart = lockEventEnd = false;
	_lockStartLine = 1200;

	/*====================================================================
		스테이지 문 만들기
	====================================================================*/
	_doorActive = DOOR_ACTIVITY::NON_ACTIVE;
	_leftDoor.isUsed = false;

	_rightDoor.isUsed = true;
	_rightDoor.LT = vector3(1310, 0, 385);
	_rightDoor.RT = vector3(1575, 0, 385);
	_rightDoor.LB = vector3(1310, 0, 430);
	_rightDoor.RB = vector3(1575, 0, 430);
	_rightDoor.img = IMG_M->findImage("UI_UnLocked_Door");

	_shopDoor.isUsed = false;


	return S_OK;
}

void EasyStage::release()
{
	Stage::release();

}

void EasyStage::update()
{
	Stage::update();
}

void EasyStage::render()
{
	Stage::render();
}
