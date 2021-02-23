#include "stdafx.h"
#include "TrayDirty.h"
#include "Character.h"
HRESULT TrayDirty::init(Character* character)
{
    _character = character;
    return S_OK;
}

STATE TrayDirty::invoke()
{
    _character->GetInfo().toolObject->SetToolType(TOOLTYPE::TRAYDIRTY);
    return STATE::SUCCESS;
}
