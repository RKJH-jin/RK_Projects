#pragma once
#include "IEnemyState.h"
class enemyWIdle : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

