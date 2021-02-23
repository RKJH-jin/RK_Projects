#include "stdafx.h"
#include "Object.h"
#include "ItemObj.h"
#include "Player.h"

HRESULT Object::init()
{
	return S_OK;
}

void Object::release()
{
}

void Object::update()
{
	_obj.update();
}

void Object::render()
{
}
