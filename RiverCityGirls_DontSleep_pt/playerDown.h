#pragma once
#include "IPlayerState.h"

class playerDown : public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

