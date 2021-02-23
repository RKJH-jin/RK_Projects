#pragma once
#include "BT.h"
#include "AllComponents.h"

class Character;

class SweepIndex : public BT::ActionNode
{
private:
	Character* _character;
	bool _handEnd;
	int _count;
public:
	HRESULT init(Character* character);
	virtual STATE invoke();
};

