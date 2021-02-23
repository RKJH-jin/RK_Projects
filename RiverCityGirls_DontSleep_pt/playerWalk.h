#pragma once
#include "IPlayerState.h"

class playerWalk :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

