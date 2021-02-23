#pragma once
#include "IPlayerState.h"

class playerStick :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

