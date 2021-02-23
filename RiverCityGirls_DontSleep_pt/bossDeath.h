#pragma once
#include"IBossState.h"

class bossDeath :public IBossState
{
private:
	float _enterTime;
	bool _UI;
	bool _event;

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};