#pragma once
#include "IEnemyState.h"
class enemyWPickup : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

