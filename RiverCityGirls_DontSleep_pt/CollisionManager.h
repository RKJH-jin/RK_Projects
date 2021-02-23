#pragma once

class StageManager;
class Player;
class Enemy;

/*====================================================================
							충돌 처리 클래스
====================================================================*/
class CollisionManager
{
private:
	StageManager* _stageM;
	Player* _player;
	Enemy* _enemy;
	bool checkLeft;
	bool checkRight;
	bool checkUp;
	bool checkDown;
	int testNum = 0;
public:
	CollisionManager() {};
	~CollisionManager() {};

	HRESULT init();
	void release();

	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkPlayer(Player* player) { _player = player; }


	/*====================================================================
									FUNCTION
	====================================================================*/
	// 전후 좌우 충돌 판정
	void LRUDCollision(GameObject* character, GameObject* obj);

	// 벽 충돌
	void playerWallCollsion();
	void enemyWallColiision(GameObject* character);

	// 충돌 함수
	void playerObjectCollision();
	void enemyObjectCollision(Enemy* enemy);


	void destructObject();
	void bossDestructObject(Enemy* enemy);
};

