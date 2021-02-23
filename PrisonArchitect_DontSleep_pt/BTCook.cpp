#include "stdafx.h"
#include "BTCook.h"
#include "Character.h"

HRESULT BTCook::init(Character * character)
{
	_character = character;
	//이거 요리중으로 바꾸는 순간에 해줘야할듯!
	_handEnd = true;
	return S_OK;
}

STATE BTCook::invoke()
{
	_character->GetTransform()->SetDirection(DIRECTION::FRONT);
	_character->GetInfo().toolObject->SetToolType(TOOLTYPE::SPATULA);
	//오른손 위치
	float centerY = _character->GetTransform()->GetPosition().GetIntY() + HANDOFFSETY;
	GameObject* leftHand = _character->GetInfo().leftHand;

	//오른쪽기준보다 작으면
	if (centerY + 5 <= leftHand->GetTransform()->GetPosition().GetIntY())
		_handEnd = false;
	//왼쪽기준보다 크면
	if (centerY - 5 >= leftHand->GetTransform()->GetPosition().GetIntY())
		_handEnd = true;

	if (_handEnd)leftHand->GetTransform()->Translate(Vector2(0, 1));
	if (!_handEnd)leftHand->GetTransform()->Translate(Vector2(0, -1));

	return STATE::SUCCESS;
}
