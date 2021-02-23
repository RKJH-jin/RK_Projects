#pragma once
#include "IPlayerState.h"

class playerDashSAttack : public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

