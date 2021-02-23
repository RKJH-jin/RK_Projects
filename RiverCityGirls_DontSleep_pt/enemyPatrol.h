#pragma once
#include "IEnemyState.h"
class enemyPatrol : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

