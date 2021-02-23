#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "player.h"
#include "mapManager.h"
#include "enemyManager.h"
#include "projectile.h"
#include "UIManager.h"
#include "startScene.h"


class playGround : public gameNode
{
private:
	camera* _mainCamera;	// 메인카메라
	player* _cPlayer;
	mapManager* _cMapManager;
	enemyManager* _cEnemyManager;
	projectile* _cProjectile;
	UIManager* _cUIManager;
	float angle = PI;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render();			//그리기 전용

	void hornetImageInit();
	void hornetAnimationInit();
	void aspidImageInit();
	void aspidAnimationInit();
	void xeroImageInit();
	void xeroAnimationInit();
};

