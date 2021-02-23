#pragma once
#include "IEnemyState.h"
class enemyLadder : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

