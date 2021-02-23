#pragma once
#include "IEnemyState.h"
class enemyStun : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

