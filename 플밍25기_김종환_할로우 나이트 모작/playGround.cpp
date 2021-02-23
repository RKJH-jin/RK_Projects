#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init(true, 7100, WINSIZEY);	// managerInit check, maxScreenWidth, maxScreenHeight
	//===========================카메라 위치 업데이트(필수)============================//
	_mainCamera = CAMERAMANAGER->getMainCamera();							// 메인카메라 가져오기
	SCENEMANAGER->addScene("startScene", new startScene);

	hornetImageInit();
	hornetAnimationInit();
	aspidImageInit();
	aspidAnimationInit();
	xeroImageInit();
	xeroAnimationInit();
	_cMapManager = new mapManager;
	_cMapManager->init();

	_cProjectile = new projectile;
	_cProjectile->init();

	_cPlayer = new player;
	_cPlayer->init();
	
	_cEnemyManager = new enemyManager;
	_cEnemyManager->init();

	_cUIManager = new UIManager;
	_cUIManager->init(200, 100);

	_cMapManager->setLinkPlayer(_cPlayer);
	_cProjectile->setLinkPlayer(_cPlayer);
	_cProjectile->setLinkEnemyManager(_cEnemyManager);
	_cEnemyManager->setLinkPlayer(_cPlayer);
	_cEnemyManager->setLinkProjectile(_cProjectile);
	_cPlayer->setLinkMapManager(_cMapManager);
	_cPlayer->setLinkProjectile(_cProjectile);
	_cPlayer->setLinkEnemyManager(_cEnemyManager);
	_cUIManager->setLinkPlayer(_cPlayer);

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();
	_cMapManager->release();
	_cPlayer->release();
	_cEnemyManager->release();
	_cProjectile->release();
}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();
	_cMapManager->update();
	_cPlayer->update();
	_cEnemyManager->update();
	_cProjectile->update();
	_cUIManager->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("startScene");
	}
	
	SCENEMANAGER->update();
	//===========================카메라 위치 업데이트(필수)============================//
	CAMERAMANAGER->mainCameraUpdate(_cPlayer->getPlayer().x, _cPlayer->getPlayer().y);			// 메인카메라 위치 업데이트! 필수!! (centerX, centerY)
}

//제발 여기다 그려라 좀...
void playGround::render()
{
	PatBlt(getMemDC(), _mainCamera->getLTX(), _mainCamera->getLTY(), WINSIZEX, WINSIZEY, WHITENESS); // getMemDC() == _backBuffer의 hMemDC를 얻는 함수
	//================ 위에 건들지 마라 ==============================
	IMAGEMANAGER->findImage("town_background")->render(getMemDC(), _mainCamera->getLTX(), _mainCamera->getLTY());
	_cMapManager->render();
	_cPlayer->render();
	_cEnemyManager->render();
	_cProjectile->render();
	_cUIManager->render(_mainCamera->getLTX() + 20, _mainCamera->getLTY() + 10);
	
	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());
	//================= 아래도 건들지 마라 ==============================
	//_backBuffer->render(getHDC());
	
	//============================카메라 랜더============================//
	// * 카메라를 안쓸꺼면 위에 _backBuffer->render의 주석처리를 지우고 쓰시면 됩니다
	_backBuffer->render(getHDC(), 0, 0, _mainCamera->getLTX(), _mainCamera->getLTY(),
		_mainCamera->getWidth(), _mainCamera->getHeight());

}





