#pragma once
#include "IPlayerState.h"

class playerHit :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

