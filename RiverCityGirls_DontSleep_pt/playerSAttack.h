#pragma once
#include "IPlayerState.h"

class playerSAttack :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

