#pragma once
#include "IEnemyState.h"

class enemyAttack3 : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

