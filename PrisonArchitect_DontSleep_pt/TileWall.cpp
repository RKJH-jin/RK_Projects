#include "stdafx.h"
#include "TileWall.h"

TileWall::TileWall(TILEWALL type)
{
	_info._type = (int)type;

	_info._attribute = TILEATTRIBUTE::WALL;
	_info._count = Vector2(1, 1);
	_type = type;

	_name = "벽 " + to_string((int)_type);
	_key = "wall" + to_string((int)_type);
	_info._img = ImageManager::GetInstance()->FindImage(_key);

	_info._price = 10 + 10 * (int)type;
	_description = _description + "\n가격은 " + to_string(_info._price) + "원입니다.";
}

HRESULT TileWall::init()
{
	return E_NOTIMPL;
}

void TileWall::release()
{
}

void TileWall::update()
{
}

void TileWall::render()
{
	_info._img->FrameRender(_info._renderPos, _info._frame.x, _info._frame.y, CAMERAMANAGER->GetMainCamera());
}

void TileWall::Build(Vector2 index)
{
	TileAttribute::Build(index);

}
BOOST_CLASS_EXPORT(TileWall)