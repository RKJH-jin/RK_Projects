#include "stdafx.h"
#include "AssignRNDGoal.h"
#include "Character.h"
#include "MapToolScene.h"

HRESULT AssignRNDGoal::init(Character * character)
{
    _character = character;
    return S_OK;
}

STATE AssignRNDGoal::invoke()
{
	_character->GetTransform()->SetPath(Vector2(RND->getInt(TILECOUNTX), RND->getInt(TILECOUNTY)));

    _character->GetTransform()->SetArriveEndIndex(false);
    return STATE::SUCCESS;
}
