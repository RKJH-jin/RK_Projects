#pragma once
#include "gameNode.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#define BGMVOLUME .1f
#define SFXVOLUME .1f

class StageManager;
/*====================================================================
	모든 스테이지는 에너미 매니저와 오브젝트 매니저를 가집니다.
	각각의 매니저를 사용해 스테이지에서 자유롭게 배치할 수 있도록 합니다.
====================================================================*/

struct tagWall
{
	image* img;
	bool isUsed;
	vector3 LT, RT, RB, LB;
	tagWall()
	{
		isUsed = false;
	}
};

class Stage : public gameNode
{
protected:
	EnemyManager* _enemyM;
	ObjectManager* _objectM;
	StageManager* _stageM;

	image* backGround;
	vector<tagWall> _vBackWall;
	vector<tagWall> _vLeftWall;
	vector<tagWall> _vRightWall;
	tagWall _floor;
	tagWall _pool;
	tagWall _leftDoor;
	tagWall _rightDoor;
	tagWall _shopDoor;

	float _zAngle;

	int _lockStartLine;
	bool lockEventStart;
	bool lockEventEnd;

	DOOR_ACTIVITY _doorActive;
	int _enemyCount;
	int _maxEnemyCount;
	float _keyTimer;

	bool activeDoor;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void backWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void leftWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void rightWallInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void floorInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);
	virtual void poolInit(vector3 lt, vector3 rt, vector3 rb, vector3 lb);

	void setLocationLockEnemyCount(int* enemyCount, int* maxEnemyCount) { enemyCount = &_enemyCount; maxEnemyCount = &_maxEnemyCount; }
	void startLocationLock(vector3 lockPos, vector3 playerPos, int maxEnemyNum);

	/*====================================================================
									GETTER
	====================================================================*/
	EnemyManager* getEnemyM() { return _enemyM; }
	ObjectManager* getObjectM() { return _objectM; }
	vector<tagWall> getLeftWall() { return _vLeftWall; }
	vector<tagWall> getBackWall() { return _vBackWall; }
	vector<tagWall> getRightWall() { return _vRightWall; }
	tagWall getFloor() { return _floor; }
	tagWall getPool() { return _pool; }
	tagWall getLeftDoor() { return _leftDoor; }
	tagWall getRightDoor() { return _rightDoor; }
	tagWall getShopDoor() { return _shopDoor; }
	DOOR_ACTIVITY getDoorActive() { return _doorActive; }
	int getEnemyCount() { return _enemyCount; }
	bool getLockEventStart() { return lockEventStart; }
	bool getLockEventEnd() { return lockEventEnd; }
	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setEnemyCount(int num) { _enemyCount = num; }
	void setLockEventStart(bool is) { lockEventStart = is; }
	void setLockEventEnd(bool is) { lockEventEnd = is; }
	/*====================================================================
									디버그용 임시함수
	====================================================================*/
	void polylineRender(vector3 A, vector3 B);
	void wallRender();

};

