#pragma once
#include "IPlayerState.h"


class playerCombo1 : public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

