#pragma once
#include "IPlayerState.h"

class playerClimbTop:public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

