#include "stdafx.h"
#include "People.h"

People::People(PEOPLEROLE role)
{
	_info.type = CHARACTERTYPE::PEOPLE;
	_role = role;
	_info.role = (int)role;
	_torso = CreateObject(this);

	switch (role)
	{
	case PEOPLEROLE::BITALIA:
		_torso->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("bitalia")); break;
	case PEOPLEROLE::BOSS:
		_torso->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("boss")); break;
	case PEOPLEROLE::NICO:
		_torso->AddComponent<ImageC>()->SetImage(IMAGEMANAGER->FindImage("nico")); break;
	}
	_torso->GetComponent<ImageC>()->SetCamera(CAMERAMANAGER->GetVCamera()[0]);
	_torso->GetTransform()->SetPivot(Vector2(0,0));

	//¼ÕÃß°¡
	CreateHands();

}

HRESULT People::init()
{
	return S_OK;
}

void People::release()
{
}

void People::update()
{
	Character::update();
	if (_torso->GetTransform()->GetDirection() == DIRECTION::RIGHT) _torso->GetComponent<ImageC>()->SetReverese(true, false);
	_torso->GetComponent<ImageC>()->SetFrame(Vector2(_info.frameX[(int)_transform->GetDirection()], 0));

}

void People::render()
{
	Character::render();

}
