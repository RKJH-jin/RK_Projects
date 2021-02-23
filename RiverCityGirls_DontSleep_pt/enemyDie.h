#pragma once
#include "IEnemyState.h"

class enemyDie : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

