#pragma once
#include "IEnemyState.h"
class enemyHardAttack : public IEnemyState
{
public :

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

