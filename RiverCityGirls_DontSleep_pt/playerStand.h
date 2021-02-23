#pragma once
#include "IPlayerState.h"

class playerStand :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

