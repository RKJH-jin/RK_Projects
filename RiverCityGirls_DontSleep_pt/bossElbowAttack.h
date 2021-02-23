#pragma once
#include"IBossState.h"

class bossElbowAttack :public IBossState
{
private:	
	float _enterTime;	
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};