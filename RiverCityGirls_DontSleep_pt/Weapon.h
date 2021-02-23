#pragma once
#include "Object.h"
class Weapon : public Object
{
public:
	Weapon(WEAPON_TYPE type, vector3 pos);
	virtual HRESULT init();
	virtual void render();
};

