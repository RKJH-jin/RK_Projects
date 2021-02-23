#pragma once
#include "IPlayerState.h"

class playerRoll :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

