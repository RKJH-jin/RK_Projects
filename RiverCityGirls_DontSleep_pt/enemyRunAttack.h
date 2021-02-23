#pragma once
#include "IEnemyState.h"
class enemyRunAttack : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();

};

