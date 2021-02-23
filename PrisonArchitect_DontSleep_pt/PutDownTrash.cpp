#include "stdafx.h"
#include "PutDownTrash.h"
#include "Character.h"
HRESULT PutDownTrash::init(Character * character)
{
    _character = character;
    return S_OK;
}

STATE PutDownTrash::invoke()
{
	_character->GetInfo().toolObject->SetToolType(TOOLTYPE::NONE);
	_character->GetInfo().isSweep = false;
    return STATE::SUCCESS;
}
