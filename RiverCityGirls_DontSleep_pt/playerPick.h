#pragma once
#include "IPlayerState.h"

class playerPick : public IPlayerState
{
public:
	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

