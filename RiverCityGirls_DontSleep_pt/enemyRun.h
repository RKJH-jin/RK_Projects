#pragma once
#include "IEnemyState.h"
class enemyRun : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

