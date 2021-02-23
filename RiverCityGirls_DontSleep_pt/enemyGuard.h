#pragma once
#include "IEnemyState.h"
class enemyGuard : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

