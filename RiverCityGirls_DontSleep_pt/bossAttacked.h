#pragma once
#include"IBossState.h"

class bossAttacked :public IBossState
{
	float _enterTime;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};