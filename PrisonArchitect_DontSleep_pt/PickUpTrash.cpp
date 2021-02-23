#include "stdafx.h"
#include "PickUpTrash.h"
#include "Character.h"

HRESULT PickUpTrash::init(Character * character)
{
    _character = character;
    return S_OK;
}

STATE PickUpTrash::invoke()
{
	_character->GetInfo().toolObject->SetToolType(TOOLTYPE::TRASH);
	_character->GetInfo().isDumping = true;
   
    return STATE::SUCCESS;
}
