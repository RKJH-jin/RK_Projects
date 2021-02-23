#pragma once
#include"IBossState.h"

class bossIdle :public IBossState
{
protected:	
	float _enterTime;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};