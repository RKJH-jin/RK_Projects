#include "stdafx.h"
#include "TileAttribute.h"


HRESULT TileAttribute::init()
{
	return S_OK;
}

void TileAttribute::release()
{
}

void TileAttribute::update()
{
}

void TileAttribute::render()
{
}

void TileAttribute::Build(Vector2 index)
{
	_info._pos = Vector2(TILESIZE * index.x, TILESIZE * index.y);
	_info._renderPos = Vector2(TILESIZE / 2 + _info._pos.x, TILESIZE / 2 + _info._pos.y);
}

void TileAttribute::Destroy()
{
}

Vector2 TileAttribute::GetCount()
{
	Vector2 result;
	switch (_info._direction)
	{
		case DIRECTION::FRONT:	case DIRECTION::BACK:
			result = _info._count;
		break;

		case DIRECTION::LEFT:	case DIRECTION::RIGHT:
			result.x = _info._count.y;
			result.y = _info._count.x;
		break;
	}

	return result;
}

Vector2 TileAttribute::GetLeftTopIndex()
{
	Vector2 result = _info._startIndex;

	return result;
}

Vector2 TileAttribute::GetCenterIndex()
{
	Vector2 result = _info._startIndex;
	result.x += (int)_info._count.x / 2;
	result.y += (int)_info._count.y / 2;
	return result;
}

Vector2 TileAttribute::GetRandomIndex()
{
	Vector2 result = _info._startIndex;
	result.x += (int)RND->getInt(_info._count.x);
	result.y += (int)RND->getInt(_info._count.y);
	return result;
}

bool TileAttribute::GetIsInArea(Vector2 index)
{
	Vector2 pos = index;

	if (_info._startIndex.x <= pos.x  && pos.x <= _info._startIndex.x + _info._count.x
		&& _info._startIndex.y <= pos.y && pos.y <= _info._startIndex.y + _info._count.y)
		return true;
	else return false;
}
BOOST_CLASS_EXPORT(TileAttribute)