#pragma once
#include "IPlayerState.h"

class playerClimb :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

