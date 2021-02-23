#pragma once
#include"IBossState.h"

class bossMeteor :public IBossState
{
private:
	float _enterTime;
	float _angle;
	float _speed;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
