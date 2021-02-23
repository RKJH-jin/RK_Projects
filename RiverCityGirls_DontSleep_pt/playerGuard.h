#pragma once
#include "IPlayerState.h"

class playerGuard : public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

