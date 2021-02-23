#pragma once
#include "BT.h"
#include "AllComponents.h"

class Character;

class BTCreateStuff : public BT::ActionNode
{
private:
	STUFFTTYPE _stuffType;
	Character* _character;

public:
	HRESULT init(Character* character);
	virtual void  setStuff(STUFFTTYPE stuff);
	virtual STATE invoke();
};


