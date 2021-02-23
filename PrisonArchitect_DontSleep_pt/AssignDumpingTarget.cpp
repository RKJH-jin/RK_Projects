#include "stdafx.h"
#include "AssignDumpingTarget.h"
#include "Character.h"

HRESULT AssignDumpingTarget::init(Character * character, Vector2 target)
{
	_character = character;
	_target = target;
	return S_OK;
}

STATE AssignDumpingTarget::invoke()
{
	if (_character->GetInfo().isDumping)
	{
		_character->GetTransform()->SetPath(_target);
		_character->GetTransform()->SetArriveEndIndex(false);
		_character->GetInfo().isDumping = false;
	}
	return STATE::SUCCESS;
}
