#pragma once
#include "IEnemyState.h"
class enemyLadderTransition : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

