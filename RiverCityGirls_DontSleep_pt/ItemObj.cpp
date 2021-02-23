#include "stdafx.h"
#include "ItemObj.h"
#include "Player.h"
ItemObj::ItemObj(ITEM_TYPE type, vector3 pos)
{
	_info.type = type;
	_info.iscollision = false;

	switch (type)
	{
	case ITEM_TYPE::MONEY:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("item_money"), pos);
		_obj.size.x = _obj.size.x/4;
		_obj.size.z = _obj.size.z/2;
		_obj.ani = new animation;
		_obj.ani->setDefPlayFrame(false, false);
		_obj.ani->setFPS(1);
		_obj.ani->init(_obj.img->getWidth(), _obj.img->getHeight(), _obj.img->getFrameWidth(), _obj.img->getFrameHeight());

		_obj.ani->start();
		_info.value = 100;

		break;
	case ITEM_TYPE::COIN:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("item_coin"), pos);
		_obj.size.x = _obj.size.x / 4;
		_obj.size.z = _obj.size.z / 2;
		_obj.ani = new animation;
		_obj.ani->setDefPlayFrame(false, true);
		_obj.ani->setFPS(1);
		_obj.ani->init(_obj.img->getWidth(), _obj.img->getHeight(), _obj.img->getFrameWidth(), _obj.img->getFrameHeight());

	    _obj.ani->start();
		_info.value = 1;
		break;
	case ITEM_TYPE::MEAT:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("item_meat"), pos);
		_info.value = 10;
		break;
	case ITEM_TYPE::APPLE:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("item_apple"), pos);
		_info.value = 10;
		break;
	case ITEM_TYPE::HEN:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("item_hen"), pos);
		_info.value = 50;
		break;
	case ITEM_TYPE::CHILI:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("item_chili"), pos);
		_info.value = 30;
		break;
	default:
		break;
	}
}

HRESULT ItemObj::init()
{
	return S_OK;
}

void ItemObj::release()
{
}

void ItemObj::update()
{
	Object::update();
	RECT temp;
	//충돌한 적이 없는데 충돌시
	//if (!_info.iscollision  && IntersectRect(&temp, &_obj.rc, &_info.player->getRefObj().rc)) _info.iscollision = true;

	if (_obj.ani)
	{
		_obj.ani->frameUpdate(TIME_M->getElapsedTime() * 5);
		if (!_obj.ani->isPlay() && _info.value == 20)_obj.ani->start();
	}
}

void ItemObj::render()
{
	switch (getInfo().type)
	{
	case ITEM_TYPE::MONEY:
	case ITEM_TYPE::COIN:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::ANI_RENDER);
		break;
	case ITEM_TYPE::MEAT:
	case ITEM_TYPE::APPLE:
	case ITEM_TYPE::HEN:
	case ITEM_TYPE::CHILI:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);
		break;
	default:
		break;
	}

}

