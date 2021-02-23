#pragma once
#include "IEnemyState.h"

class enemyDown : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

