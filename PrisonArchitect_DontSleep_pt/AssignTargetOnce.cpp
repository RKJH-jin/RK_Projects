#include "stdafx.h"
#include "AssignTargetOnce.h"
#include "Character.h"

HRESULT AssignTargetOnce::init(Character* character, Vector2 target)
{
	_character = character;
	_target = target;
	return S_OK;
}

STATE AssignTargetOnce::invoke()
{
	//◈타게팅한상태거나 도착했다면 타게팅하지않고 리턴
	if (_character->GetInfo().goalState == GOALSTATE::GOALSET || _character->GetInfo().goalState == GOALSTATE::GOALREACH) return STATE::SUCCESS;
	_character->GetTransform()->SetPath(_target);
	_character->GetTransform()->SetArriveEndIndex(false);
	//◈타게팅한상태로 변경
	_character->GetInfo().goalState = GOALSTATE::GOALSET;
	return STATE::SUCCESS;
}
