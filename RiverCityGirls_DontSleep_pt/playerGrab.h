#pragma once
#include "IPlayerState.h"

class playerGrab :public IPlayerState
{
	bool _fail;
public:
	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

