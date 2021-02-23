#pragma once
#include"IBossState.h"

class bossWait :public IBossState
{
private: 
	float _enterTime;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
