#pragma once
#include "gameNode.h"

class Boss;
class Enemy;
class StageManager;
/*====================================================================
	에너미 매니저입니다. 에너미를 벡터에 넣어 관리하며,
	push로 에너미를 집어 넣고, pop으로 뺄 수 있습니다.
====================================================================*/

class EnemyManager : public gameNode
{
private:
	Boss* _boss;
	vector<Enemy*> _vEnemy;
	StageManager* _stageM;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pushEnemy(ENEMY_TYPE type, vector3 pos);
	void popEnemy(int index);

	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	vector<Enemy*> getVEnemy() { return _vEnemy; }

};

