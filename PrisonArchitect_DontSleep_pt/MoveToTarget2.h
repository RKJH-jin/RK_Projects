#pragma once
#include "BT.h"
#include "AllComponents.h"

class Character;

class MoveToTarget2 : public BT::ActionNode
{
private:
	Character* _character;

public:
	HRESULT init(Character* character);
	virtual STATE invoke();
};


