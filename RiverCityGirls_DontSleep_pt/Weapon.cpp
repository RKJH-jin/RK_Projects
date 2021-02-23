#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(WEAPON_TYPE type, vector3 pos)
{
	
	switch (type)
	{
	case WEAPON_TYPE::BAT:
		_obj.init(OBJECT_GROUP::WEAPON, IMG_M->findImage("bat"), pos);
		_obj.weaponType = WEAPON_TYPE::BAT;
		break;
	case WEAPON_TYPE::BASEBALL:
		//_obj.init(OBJECT_GROUP::WEAPON, IMG_M->findImage("baseball"), pos);
		_obj.weaponType = WEAPON_TYPE::BASEBALL;

		break;
	default:
		break;
	}
}

HRESULT Weapon::init()
{
	return S_OK;
}

void Weapon::render()
{
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
}
