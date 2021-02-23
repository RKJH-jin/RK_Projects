#pragma once
#include "gameNode.h"
#include "Enemy.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h""

class Enemy;

class IEnemyState abstract
{
protected:
	Enemy* _thisEn;
	
	//float _a1;
	//float _a2;
	float _stateTimer;
	vector3 _tempPos;
	bool _isGoBack;
	bool wait;
	bool _money;
	float tempAngle;
	float _checkTimer;
	float _hitIdxTimer;
	bool isDown;
public:
	IEnemyState() {}
	~IEnemyState() {}

	void LinkEnemeyAddress(Enemy* en) { _thisEn = en; }

	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;


	void Jump();
	void LookAtPlayer();
	void Attack();
	bool endFrame();
	void Damage(int atk);
};

