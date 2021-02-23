#pragma once
#include "IEnemyState.h"
class enemyJumpAttack : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

