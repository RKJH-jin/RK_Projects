#pragma once
#include "BT.h"
#include "AllComponents.h"

class Character;

class BTCook : public BT::ActionNode
{
private:
	Character* _character;
	bool _handEnd;
public:
	HRESULT init(Character* character);
	virtual STATE invoke();
};


