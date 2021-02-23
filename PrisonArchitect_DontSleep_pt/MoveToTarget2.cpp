#include "stdafx.h"
#include "MoveToTarget2.h"
#include "Character.h"

HRESULT MoveToTarget2::init(Character* character)
{
	_character = character;
	return S_OK;
}

STATE MoveToTarget2::invoke()
{
	if (!_character->GetTransform()->GetHaveTarget() && !_character->GetTransform()->GetPath().empty())
	{
		_character->GetTransform()->SetTarget(_character->GetTransform()->GetPath().top());
		_character->GetTransform()->GetPath().pop();
		_character->GetTransform()->SetHaveTarget(true);
	}

	if (_character->GetTransform()->GetHaveTarget() && _character->GetTransform()->GetIndex() != _character->GetTransform()->GetTarget())
	{

		int dx = _character->GetTransform()->GetTarget().x - _character->GetTransform()->GetIndex().x;
		int dy = _character->GetTransform()->GetTarget().y - _character->GetTransform()->GetIndex().y;

		if (dx != 0)
		{
			if (dx > 0)
			{
				_character->GetTransform()->Translate(Vector2(_character->GetInfo().moveSpeed * DATAMANAGER->GetInfo().gameSpeed, (float)0));
			}
			else
			{
				_character->GetTransform()->Translate(Vector2(-_character->GetInfo().moveSpeed * DATAMANAGER->GetInfo().gameSpeed, (float)0));
			}
		}
		if (dy != 0)
		{
			if (dy > 0)
			{
				_character->GetTransform()->Translate(Vector2((float)0, _character->GetInfo().moveSpeed * DATAMANAGER->GetInfo().gameSpeed));
			}
			else
			{
				_character->GetTransform()->Translate(Vector2((float)0, -_character->GetInfo().moveSpeed * DATAMANAGER->GetInfo().gameSpeed));
			}
		}

		_character->GetTransform()->SetIndex(Vector2((int)(_character->GetTransform()->GetPosition().x / TILESIZE), (int)(_character->GetTransform()->GetPosition().y / TILESIZE)));

		if (_character->GetTransform()->GetIndex() == _character->GetTransform()->GetTarget())
		{
			_character->GetTransform()->SetHaveTarget(false);
		}
	}

	if (_character->GetTransform()->GetIndex() == _character->GetTransform()->GetEndIndex())
	{
		_character->GetTransform()->SetArriveEndIndex(true);
		_character->GetInfo().goalState = GOALSTATE::NONE;
	}
	return STATE::SUCCESS;
}
