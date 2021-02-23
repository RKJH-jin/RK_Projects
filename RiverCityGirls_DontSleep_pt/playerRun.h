#pragma once
#include "IPlayerState.h"

class playerRun :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

