#pragma once
#include "IPlayerState.h"

class playerJumpAttack :public IPlayerState
{
	bool _isEffect;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

