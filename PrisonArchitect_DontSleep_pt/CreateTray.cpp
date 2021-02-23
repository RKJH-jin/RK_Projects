#include "stdafx.h"
#include "CreateTray.h"
#include "Character.h"
HRESULT CreateTray::init(Character* character)
{
    _character = character;
    return S_OK;
}

STATE CreateTray::invoke()
{
    _character->GetInfo().countTime += TIMEMANAGER->getElapsedTime();
    if (_character->GetInfo().countTime > 1.5f)
    {
        _character->GetInfo().btState = BTSTATE::NONE;
        _character->GetInfo().toolObject->SetToolType(TOOLTYPE::TRAY);
        _character->GetInfo().toolObject->setLinkCharacter(_character);
    }
    return STATE::SUCCESS;
}
