#pragma once
#include "IPlayerState.h"

class playerLadder :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

