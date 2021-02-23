#pragma once
#pragma once
#include "BT.h"
#include "AllComponents.h"

class Character;

class CreateTray : public BT::ActionNode
{
private:
    Character* _character;

public:
    HRESULT init(Character* character);
    virtual STATE invoke();
};
