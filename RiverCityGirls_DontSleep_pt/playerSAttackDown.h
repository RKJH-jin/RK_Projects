#pragma once
#include "IPlayerState.h"

class playerSAttackDown :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

