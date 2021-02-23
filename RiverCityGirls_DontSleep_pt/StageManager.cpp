#include "stdafx.h"
#include "StageManager.h"

#include "Player.h"
#include "CollisionManager.h"

#include "Stage.h"
#include "EasyStage.h"
#include "NormalStage.h"
#include "HardStage.h"
#include "BossStage.h"

/*====================================================================
	초기화에서 플래이어를 만들어 주며, 첫 스테이지를 설정합니다.
	기본 값은 EASY이며, 실험하고 싶은 스테이지로 설정하면 해당 스테이지로 세팅됩니다.
====================================================================*/
HRESULT StageManager::init()
{
	//플래이어 객체 생성
	_player = new Player;
	_player->init();
	_player->setLinkStageM(this);
	EVENT_M->setLinkPlayer(_player);

	//첫 스테이지 세팅
	if (DATA_M->getStage(DATA_M->getFileNum()) == -1) setStage(STAGETYPE::EASY);

	return S_OK;
}

/*====================================================================
	Player와 Stage의 메모리를 삭제해 줍니다.
====================================================================*/
void StageManager::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_stage->release();
	SAFE_DELETE(_stage);
}


/*====================================================================
	Player와 Stage에 대한 걸 업데이트 하며,
	이벤트가 실행 중이지 않을 때에는 카메라가 플래이어를 따라 갑니다.
====================================================================*/
void StageManager::update()
{
	_stage->update();
	_player->update();
	if (!EVENT_M->getIsCameraMove())

	CAMERA_M->SetPos(_player->getObj().pos.x, _player->getObj().pos.z + _player->getObj().pos.y, 0, 0, 4.5f);
/*
	{
		if (KEY_M->isStayKeyDown('O')) CAMERA_M->SetMagnification(CAMERA_M->GetMagnificiation() + 0.01f);
		if (KEY_M->isStayKeyDown('L')) CAMERA_M->SetMagnification(CAMERA_M->GetMagnificiation() - 0.01f);

		if (KEY_M->isStayKeyDown('K')) CAMERA_M->SetPos(1200, 0, 0,0,6);
		if (KEY_M->isStayKeyDown('J')) CAMERA_M->SetPos(0, 0, 0, 0, 6);
	}*/

	

	changeStage();
#ifdef _DEBUG
	// 디버그용 스테이지 이동
	if (KEY_M->isOnceKeyDown(VK_F1)) setStage(STAGETYPE::EASY);
	if (KEY_M->isOnceKeyDown(VK_F2)) setStage(STAGETYPE::NORMAL);
	if (KEY_M->isOnceKeyDown(VK_F3)) setStage(STAGETYPE::HARD);
	if (KEY_M->isOnceKeyDown(VK_F4)) setStage(STAGETYPE::BOSS);
#endif
}

/*====================================================================
	Player와 Stage를 렌더 합니다.
====================================================================*/
void StageManager::render()
{
	_stage->render();
	_player->render();
}

/*====================================================================
	setStage 함수는 enum class STAGETYPE을 인자값으로 받아,
	현제 스테이지를 해당 스테이지로 설정 해 줍니다.
====================================================================*/
void StageManager::setStage(STAGETYPE current)
{
	if (_stage != NULL)
	{
		if (_currentStage == current) return;	//현재 스테이지와 같을 경우 스테이지를 바꾸지 않는다.

		_stage->release();		//스테이지가 비어있지 않으면, 바꾸기 전에
		SAFE_DELETE(_stage);	//메모리를 날려 주고 딜리트 해 준다.
	}

	_preStage = _currentStage;
	_currentStage = current;	//현재 스테이지를 바꿔 준다.
	if(_currentStage != STAGETYPE::BOSS) EVENT_M->addEvent(new heart(false), false);

	//새로운 스테이지 객체를 생성하고, 초기화한다.
	switch (_currentStage)
	{
	case STAGETYPE::EASY:
		_stage = new EasyStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::NORMAL:
		_stage = new NormalStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::HARD:
		_stage = new HardStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::BOSS:
		_stage = new BossStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;
	}

	//플래이어가 스테이지 초기화를 한다.
	_player->stageInit();
}

void StageManager::changeStage()
{
	if (EVENT_M->getIsEvent()) return;
	if (getStage()->getLockEventStart() == false || getStage()->getLockEventEnd() == true)
	{
		if (KEY_M->isStayKeyDown('M'))
		{
			_keyTimer += TIME_M->getElapsedTime();
			if (_keyTimer >= 1.0f || true)
			{
				switch (_currentStage)
				{
				case STAGETYPE::EASY:
					if (_stage->getRightDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getRightDoor().RB.z &&
						_stage->getRightDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getRightDoor().RB.x)
					{
						setStage(STAGETYPE::NORMAL);
						_keyTimer = 0;
					}
					break;
				case STAGETYPE::NORMAL:
					if (_stage->getLeftDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getLeftDoor().RB.z &&
						_stage->getLeftDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getLeftDoor().RB.x)
					{
						setStage(STAGETYPE::EASY);
						_keyTimer = 0;
					}
					else if (_stage->getRightDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getRightDoor().RB.z &&
						_stage->getRightDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getRightDoor().RB.x)
					{
						setStage(STAGETYPE::HARD);
						_keyTimer = 0;
					}
					else if (_stage->getShopDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getShopDoor().RB.z &&
						_stage->getShopDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getShopDoor().RB.x)
					{
						SOUND_M->playSFX("shop_voice");
						DATA_M->saveStageData();
						SCENE_M->setInitScene("shop");	//상점 입장
						_keyTimer = 0;
					}
					break;

				case STAGETYPE::HARD:
					if (_stage->getLeftDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getLeftDoor().RB.z &&
						_stage->getLeftDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getLeftDoor().RB.x)
					{
						setStage(STAGETYPE::NORMAL);
						_keyTimer = 0;
					}
					else if (_stage->getRightDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getRightDoor().RB.z &&
						_stage->getRightDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getRightDoor().RB.x)
					{
						setStage(STAGETYPE::BOSS);
						_keyTimer = 0;
					}
					break;
				case STAGETYPE::BOSS:
					if (_stage->getLeftDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getLeftDoor().RB.z &&
						_stage->getLeftDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getLeftDoor().RB.x)
					{
						setStage(STAGETYPE::HARD);
						_keyTimer = 0;
					}
					break;
				default:
					break;
				}
			}

		}
	}
}
