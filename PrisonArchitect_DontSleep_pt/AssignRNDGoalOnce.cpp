#include "stdafx.h"
#include "AssignRNDGoalOnce.h"
#include "Character.h"
#include "MapToolScene.h"
HRESULT AssignRNDGoalOnce::init(Character * character)
{
	_character = character;
	return S_OK;
}

STATE AssignRNDGoalOnce::invoke()
{
	//◈타게팅한상태거나 도착했다면 타게팅하지않고 리턴
	if (_character->GetInfo().goalState == GOALSTATE::GOALSET || _character->GetInfo().goalState == GOALSTATE::GOALREACH) return STATE::SUCCESS;
	_character->GetTransform()->SetPath(Vector2(RND->getInt(TILECOUNTX), RND->getInt(TILECOUNTY)));
	_character->GetTransform()->SetArriveEndIndex(false);
	//◈타게팅한상태로 변경
	_character->GetInfo().goalState = GOALSTATE::GOALSET;
	return STATE::SUCCESS;
}
