#pragma once
#include "IPlayerState.h"

class playerJump :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

