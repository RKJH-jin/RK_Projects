#pragma once
#include "IEnemyState.h"
class enemyFriend : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

