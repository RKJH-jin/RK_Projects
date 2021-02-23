#pragma once
#include "IEnemyState.h"
class enemyWWalk : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

