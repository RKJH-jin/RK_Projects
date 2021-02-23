#include "stdafx.h"
#include "SweepIndex.h"
#include "Character.h"

HRESULT SweepIndex::init(Character * character)
{
	_character = character;
	
	return S_OK;
}

STATE SweepIndex::invoke()
{
	_character->GetInfo().toolObject->SetToolType(TOOLTYPE::MOP);
	

	//오른손 위치
   float centerX = _character->GetTransform()->GetPosition().GetIntX() + HANDOFFSETX;
   GameObject* leftHand = _character->GetInfo().leftHand;
   
   //오른쪽기준보다 작으면
   if (centerX + 10 <= leftHand->GetTransform()->GetPosition().GetIntX())
      _handEnd = false;
      //왼쪽기준보다 크면
   if (centerX - 10 >= leftHand->GetTransform()->GetPosition().GetIntX())
      _handEnd = true;

   if(_handEnd)leftHand->GetTransform()->Translate(Vector2(1, 0));
   if(!_handEnd)leftHand->GetTransform()->Translate(Vector2(-1, 0));

   _count++;

	if (_count > 200)
	{
		_character->GetInfo().toolObject->SetToolType(TOOLTYPE::NONE);
		_character->GetInfo().isSweep = true;
		_count = 0;

	}
	
	return STATE::SUCCESS;
}
