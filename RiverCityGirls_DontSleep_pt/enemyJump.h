#pragma once
#include "IEnemyState.h"
class enemyJump : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

