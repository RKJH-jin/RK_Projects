#include "stdafx.h"
#include "PrisonerEat.h"
#include "Character.h"
HRESULT PrisonerEat::init(Character* character)
{
    _character = character;
    num = 1;
    return S_OK;
}

STATE PrisonerEat::invoke()
{

    TransformC* leftH = _character->GetInfo().leftHand->GetTransform();
    TransformC* rightH = _character->GetInfo().leftHand->GetTransform();
    if (num == 1)
    {
        leftH->SetPosition(leftH->GetPosition() + Vector2(0, 10));
        rightH->SetPosition(leftH->GetPosition() + Vector2(0, -10));
        num = -1;
        return STATE::SUCCESS;
    }

    else if (num == -1)
    {
        leftH->SetPosition(leftH->GetPosition() + Vector2(0, -10));
        rightH->SetPosition(leftH->GetPosition() + Vector2(0, 10));
        num = 1;
        return STATE::SUCCESS;
    }
}
