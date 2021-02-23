#pragma once
#include "BT.h"
#include "AllComponents.h"

class Character;

class PrisonerEat : public BT::ActionNode
{
private:
    Character* _character;
    int num;
public:
    HRESULT init(Character* character);
    virtual STATE invoke();
};

