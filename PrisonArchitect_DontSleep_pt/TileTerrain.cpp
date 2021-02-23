#include "stdafx.h"
#include "TileTerrain.h"

TileTerrain::TileTerrain(TILETERRAIN type)
{
	_info._type = (int)type;

	_info._frame.x = _info._type / 10 * 5;
	_info._frame.y = _info._type % 10 * 2;

	_info._attribute = TILEATTRIBUTE::TERRAIN;
	_info._count = Vector2(1, 1);
	_type = type;
	_info._price = 50;

	switch (type)
	{
	case TILETERRAIN::GRASS1:
		_name = _key = "GRASS1";
		_info._price = 0;
		break;
	case TILETERRAIN::GRASS2:
		_name = _key = "GRASS2";
		break;
	case TILETERRAIN::GRASS3:
		_name = _key = "GRASS3";
		break;
	case TILETERRAIN::GROUND:
		_name = _key = "GROUND";
		break;
	case TILETERRAIN::CONCRETE1:
		_name = _key = "CONCRETE1";
		break;
	case TILETERRAIN::CONCRETE2:
		_name = _key = "CONCRETE2";
		break;
	case TILETERRAIN::CONCRETE3:
		_name = _key = "CONCRETE3";
		break;
	case TILETERRAIN::FLOOR:
		_name = _key = "FLOOR";
		break;
	case TILETERRAIN::ROAD:
		_name = _key = "ROAD";
		break;
	case TILETERRAIN::ASPHALT:
		_name = _key = "ASPHALT";
		break;
	case TILETERRAIN::MUD:
		_name = _key = "MUD";
		break;
	case TILETERRAIN::BRICK:
		_name = _key = "BRICK";
		break;
	case TILETERRAIN::ROCK:
		_name = _key = "ROCK";
		break;
	case TILETERRAIN::MOON:
		_name = _key = "MOON";
		break;
	case TILETERRAIN::FLOOR2:
		_name = _key = "FLOOR2";
		break;
	case TILETERRAIN::FLOWER:
		_name = _key = "FLOWER";
		break;
	case TILETERRAIN::CRACK:
		_name = _key = "CRACK";
		break;
	case TILETERRAIN::TILE:
		_name = _key = "TILE";
		break;
	case TILETERRAIN::CARPET:
		_name = _key = "CARPET";
		break;
	case TILETERRAIN::MONO:
		_name = _key = "MONO";
		break;
	case TILETERRAIN::END:
		break;
	default:
		break;
	}
	_description = _name + "입니다." + "\n가격은 " + to_string(_info._price) + "원입니다.";

}

HRESULT TileTerrain::init()
{
	return E_NOTIMPL;
}

void TileTerrain::release()
{
}

void TileTerrain::update()
{
}

void TileTerrain::render()
{
	DATAMANAGER->GetTerrainImage()->FrameRender(_info._renderPos, _info._frame.x, _info._frame.y, CAMERAMANAGER->GetMainCamera());
}

void TileTerrain::Build(Vector2 index)
{
	TileAttribute::Build(index);
}
BOOST_CLASS_EXPORT(TileTerrain)