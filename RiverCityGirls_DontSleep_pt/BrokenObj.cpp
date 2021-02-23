#include "stdafx.h"
#include "BrokenObj.h"

BrokenObj::BrokenObj(OBJECT_TYPE type, vector3 pos)
{
	switch (type)
	{
	case OBJECT_TYPE::VENDINGMACHINE:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::VENDINGMACHINE, IMG_M->findImage("vendingMachine"), pos, 60);
		_type = type;
		break;
	case OBJECT_TYPE::PILLAR_LEFT:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::PILLAR_LEFT, IMG_M->findImage("pillar"), pos, 68);
		_type = type;
		break;
	case OBJECT_TYPE::PILLAR_RIGHT:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::PILLAR_RIGHT, IMG_M->findImage("pillar"), pos, 68);
		_type = type;
		break;
	case OBJECT_TYPE::PILLAR_BIG_LEFT:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::PILLAR_BIG_LEFT, IMG_M->findImage("pillar_big"), pos, 68);
		_type = type;
		break;
	case OBJECT_TYPE::PILLAR_BIG_RIGHT:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::PILLAR_BIG_RIGHT, IMG_M->findImage("pillar_big"), pos, 68);
		_type = type;
		break;
	default:
		break;
	}
}

HRESULT BrokenObj::init()
{
	return S_OK;
}

void BrokenObj::release()
{
}

void BrokenObj::update()
{
}

void BrokenObj::render()
{
	switch (_type)
	{
	case OBJECT_TYPE::VENDINGMACHINE:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
		break;
	case OBJECT_TYPE::PILLAR_LEFT:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
		break;
	case OBJECT_TYPE::PILLAR_RIGHT:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
		break;
	case OBJECT_TYPE::PILLAR_BIG_LEFT:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
		break;
	case OBJECT_TYPE::PILLAR_BIG_RIGHT:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
		break;
	default:
		break;
	}
}

