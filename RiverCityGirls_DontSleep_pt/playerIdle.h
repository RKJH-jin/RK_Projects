#pragma once
#include "IPlayerState.h"

class playerIdle :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

