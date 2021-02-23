#pragma once
#include "IEnemyState.h"

class enemyHit2 : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

