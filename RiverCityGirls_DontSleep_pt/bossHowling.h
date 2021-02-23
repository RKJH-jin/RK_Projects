#pragma once
#include "IBossState.h"

class bossHowling :public IBossState
{
private:
	float _enterTime;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};