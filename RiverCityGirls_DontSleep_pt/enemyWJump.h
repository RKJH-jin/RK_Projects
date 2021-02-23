#pragma once
#include "IEnemyState.h"
class enemyWJump : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

