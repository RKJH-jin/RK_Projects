#pragma once
#include "IEnemyState.h"
class enemyWThrow : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

