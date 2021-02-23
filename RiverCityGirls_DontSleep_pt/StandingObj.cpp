#include "stdafx.h"
#include "StandingObj.h"

StandingObj::StandingObj(OBJECT_TYPE type, vector3 pos)
{
	switch (type)
	{
	case OBJECT_TYPE::DESK:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::DESK, IMG_M->findImage("desk"), pos, 70); //58
		_type = type;
		break;
	case OBJECT_TYPE::TABLE:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::TABLE, IMG_M->findImage("table"), pos, 50); //58
		_type = type;
		break;
	case OBJECT_TYPE::LADDER:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::LADDER, nullptr, pos, 10);
		_type = type;
		break;
	case OBJECT_TYPE::HARDPLATFORM:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::HARDPLATFORM, nullptr, pos, 0); //58
		_type = type;
		break;
	case OBJECT_TYPE::PILLAR_PARTICLE_1:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::PILLAR_PARTICLE_1, IMG_M->findImage("pillar_particle_1"), pos, 0); //58
		_type = type;
		break;
	case OBJECT_TYPE::PILLAR_PARTICLE_2:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::PILLAR_PARTICLE_2, IMG_M->findImage("pillar_particle_2"), pos, 0); //58
		_type = type;
		break;
	case OBJECT_TYPE::PILLAR_PARTICLE_3:
		_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::PILLAR_PARTICLE_3, IMG_M->findImage("pillar_particle_3"), pos, 0); //58
		_type = type;
		break;
	default:
		break;
	}
}

HRESULT StandingObj::init()
{
	return S_OK;
}

void StandingObj::release()
{
}

void StandingObj::update()
{
}

void StandingObj::render()
{
	switch (_type)
	{
	case OBJECT_TYPE::DESK:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);

		break;
	case OBJECT_TYPE::TABLE:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);

		break;
	case OBJECT_TYPE::PILLAR_PARTICLE_1:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);

		break;
	case OBJECT_TYPE::PILLAR_PARTICLE_2:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);

		break;
	case OBJECT_TYPE::PILLAR_PARTICLE_3:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);

		break;
	default:
		break;
	}

}
