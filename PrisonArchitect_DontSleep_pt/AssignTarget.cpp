#include "stdafx.h"
#include "AssignTarget.h"
#include "Character.h"

HRESULT AssignTarget::init(Character* character, Vector2 target)
{
	_character = character;
    _target = target;
	return S_OK;
}

STATE AssignTarget::invoke()
{
    _character->GetTransform()->SetPath(_target);
    _character->GetTransform()->SetArriveEndIndex(false);
	return STATE::SUCCESS;
}
