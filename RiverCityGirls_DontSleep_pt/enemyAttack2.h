#pragma once
#include "IEnemyState.h"

class enemyAttack2 : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

