#pragma once
#include "IEnemyState.h"
class enemyWeaponHit : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

