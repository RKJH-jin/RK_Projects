#pragma once
#include "BT.h"
#include "AllComponents.h"

class Character;

class AssignTargetOnce : public BT::ActionNode
{
private:
	Character* _character;
	Vector2 _target;
public:
	HRESULT init(Character* character, Vector2 target);
	virtual STATE invoke();
};

