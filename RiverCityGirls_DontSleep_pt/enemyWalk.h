#pragma once
#include "IEnemyState.h"
class enemyWalk : public IEnemyState
{
	
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

