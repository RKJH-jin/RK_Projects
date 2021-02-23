#pragma once
#include "IPlayerState.h"

class playerStomp :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

