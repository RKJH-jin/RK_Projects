#pragma once
#include "IPlayerState.h"

class playerWait :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

