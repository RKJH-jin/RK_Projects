#pragma once
#include "Scene.h"
#include <string>

#define PLAYERHP 31
class StageManager;
class CollisionManager;


/*====================================================================
	게임 씬입니다. 게임 씬은 StageManager를 가집니다.
====================================================================*/
class tagUI
{
public:
	image* img;
	vector3 pos;
};
class GameScene : public Scene
{
private:
	StageManager* _stageM;
	CollisionManager* _colM;
	tagUI _playerHP[PLAYERHP];

public:
	GameScene() {}
	~GameScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void PlayerUI();
};