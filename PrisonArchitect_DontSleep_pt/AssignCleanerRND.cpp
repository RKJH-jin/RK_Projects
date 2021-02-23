#include "stdafx.h"
#include "AssignCleanerRND.h"
#include "Character.h"
#include "MapToolScene.h"

HRESULT AssignCleanerRND::init(Character * character)
{
	_character = character;
	return S_OK;
}

STATE AssignCleanerRND::invoke()
{
	if (_character->GetTransform()->GetIndex() == _character->GetTransform()->GetEndIndex() || _character->GetInfo().isStart)
	{
		_character->GetTransform()->SetPath(Vector2(RND->getInt(60), RND->getInt(50)));
		_character->GetTransform()->SetArriveEndIndex(false);
		_character->GetInfo().isStart = false;
	}
	return STATE::SUCCESS;
}
