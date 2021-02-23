#include "stdafx.h"
#include "TileMap.h"
#include "JumpPointSearch.h"

#include "TileAttribute.h"
#include "TileTerrain.h"

HRESULT TileMap::init()
{
	return S_OK;
}

void TileMap::release()
{
}

void TileMap::update()
{
}

void TileMap::render()
{
	//바닥 렌더
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_terrain && _vTile[i]->_terrain->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_terrain->render();
	}

	//지역 렌더
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_area && _vTile[i]->_area->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_area->render();
	}
	
	//벽 렌더
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_wall && _vTile[i]->_wall->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_wall->render();
	}

	
	//오브젝트 렌더
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_tileObj && _vTile[i]->_tileObj->GetInfo()._startIndex == Vector2(i % (int)_count.x, i / (int)_count.x)) _vTile[i]->_tileObj->render();
	}
	
}
void TileMap::SetTileMap(Vector2 count)
{
	//x, y 인덱스 개수를 정한다.
	_count = count;

	//타일 총 개수를 구한다.
	_tileCount = _count.x * _count.y;

	for (int i = 0; i < _tileCount; i++)
	{
		Tile* tile = new Tile;

		tile->_index = Vector2(i % (int)_count.x, i / (int)_count.x);

		_vTile.push_back(tile);

		BuildTileObject(tile->_index, DATAMANAGER->CreateTileObject("GRASS1"));
		tile->_wall = NULL;
		tile->_tileObj = NULL;
	}

}

void TileMap::BuildTileObject(Vector2 index, TileAttribute * tileObj)
{
	//예외에 해당하면 만들지 않음.
	if (!CanBuildTile(index, tileObj)) return;

	tileObj->GetInfo()._startIndex = index;

	switch (tileObj->GetInfo()._attribute)
	{
	case TILEATTRIBUTE::END:

		break;
	case TILEATTRIBUTE::TERRAIN:
	{
		_vTile[index.y * _count.x + index.x]->_terrain = tileObj;
		tileObj->Build(index);
	}
	break;
	case TILEATTRIBUTE::WALL:
	{
		//이미 벽이 있는데
		if (_vTile[index.y * _count.x + index.x]->_wall)
		{
			//타입이 다르다면 이전 타일의 메모리를 삭제한다.
			delete _vTile[index.y * _count.x + index.x]->_wall;
			_vTile[index.y * _count.x + index.x]->_wall = NULL;
		}

		//타일을 생성 해 준다.
		tileObj->Build(index);

		_vTile[index.y * _count.x + index.x]->_wall = tileObj;
		_vTile[index.y * _count.x + index.x]->_wall->GetInfo()._startIndex = index;

		//주변 네 타일을 검사하고 프레임을 바꿔 준다.
		_vTile[index.y * _count.x + index.x]->_wall->GetInfo()._frame = (GetWallFrame(index, tileObj));

		//상
		if(index.y - 1 >= 0 && _vTile[(index.y - 1) * _count.x + index.x]->_wall)
		{
			_vTile[(index.y - 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y - 1), tileObj);
		}
		//하
		if (index.y + 1 < _count.y && _vTile[(index.y + 1) * _count.x + index.x]->_wall)
		{
			_vTile[(index.y + 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y + 1), tileObj);
		}
		//좌
		if (index.x - 1 >= 0 && _vTile[index.y * _count.x + index.x - 1]->_wall)
		{
			_vTile[index.y * _count.x + index.x - 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x - 1, index.y), tileObj);
		}
		//우
		if (index.x + 1 < _count.x &&_vTile[index.y * _count.x + index.x + 1]->_wall)
		{
			_vTile[index.y * _count.x + index.x + 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x + 1, index.y), tileObj);
		}

	}
	break;
	case TILEATTRIBUTE::OBJECT:
	{
		//방향이 오른쪽 또는 왼쪽이라면 차지하는 x, y 칸의 개수를 뒤집어 검사 해 준다.
		Vector2 count = tileObj->GetInfo()._count;
		if (tileObj->GetInfo()._direction == DIRECTION::RIGHT || tileObj->GetInfo()._direction == DIRECTION::LEFT)
		{
			count.x = tileObj->GetInfo()._count.y;
			count.y = tileObj->GetInfo()._count.x;
		}

		//예외에 해당하면 만들지 않음.
		if (!CanBuildTile(index, tileObj)) return;
		

		//해당 타일에 인덱스를 만들고, 오브젝트의 시작 인덱스로 설정한다.
		tileObj->Build(index);

		for (int i = 0; i < count.x; i++)
		{
			for (int j = 0; j < count.y; j++)
			{
				//카운트 인덱스를 전부 해당 오브젝트로 링크 시켜 준다.
				_vTile[(index.y + j) * _count.x + index.x + i]->_tileObj = tileObj;
			}
		}
	}
	break;
	case TILEATTRIBUTE::AREA:
	{
		tileObj->GetInfo()._startIndex = index;
		Vector2 count = tileObj->GetInfo()._count;

		for (int i = 0; i < count.x; i++)
		{
			for (int j = 0; j < count.y; j++)
			{
				if (!CanBuildTile(Vector2(index.x+i,index.y+j), tileObj)) return;
			}
		}

		tileObj->Build(index);

		for (int i = 0; i < count.x; i++)
		{
			for (int j = 0; j < count.y; j++)
			{
				//카운트 인덱스를 전부 해당 오브젝트로 링크 시켜 준다.
				_vTile[(index.y + j) * _count.x + index.x + i]->_area = tileObj;
			}
		}
	}
	break;
	}
	DATAMANAGER->GetInfo().money -= tileObj->GetInfo()._price;
}

void TileMap::DestroyTileObject(TileAttribute * tileObj)
{
	switch (tileObj->GetInfo()._attribute)
	{
		case TILEATTRIBUTE::TERRAIN:
		{
		}
		break;
		case TILEATTRIBUTE::WALL:
		{
			Vector2 index = tileObj->GetInfo()._startIndex;
			delete tileObj;

			_vTile[index.x + index.y * _count.x]->_wall = NULL;

			//상
			if (index.y - 1 >= 0 && _vTile[(index.y - 1) * _count.x + index.x]->_wall)
			{
				_vTile[(index.y - 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y - 1), tileObj);
			}
			//하
			if (index.y + 1 < _count.y && _vTile[(index.y + 1) * _count.x + index.x]->_wall)
			{
				_vTile[(index.y + 1) * _count.x + index.x]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x, index.y + 1), tileObj);
			}
			//좌
			if (index.x - 1 >= 0 && _vTile[index.y * _count.x + index.x - 1]->_wall)
			{
				_vTile[index.y * _count.x + index.x - 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x - 1, index.y), tileObj);
			}
			//우
			if (index.x + 1 < _count.x &&_vTile[index.y * _count.x + index.x + 1]->_wall)
			{
				_vTile[index.y * _count.x + index.x + 1]->_wall->GetInfo()._frame = GetWallFrame(Vector2(index.x + 1, index.y), tileObj);
			}
		}
		break;
		case TILEATTRIBUTE::OBJECT:
		{
			//방향이 오른쪽 또는 왼쪽이라면 차지하는 x, y 칸의 개수를 뒤집어 검사 해 준다.
			Vector2 count = tileObj->GetInfo()._count;
			if (tileObj->GetInfo()._direction == DIRECTION::RIGHT || tileObj->GetInfo()._direction == DIRECTION::LEFT)
			{
				count.x = tileObj->GetInfo()._count.y;
				count.y = tileObj->GetInfo()._count.x;
			}

			//시작 인덱스에서부터 개수까지의 타일에서 돌린다.
			for (int i = tileObj->GetInfo()._startIndex.x; i < tileObj->GetInfo()._startIndex.x + count.x; i++)
			{
				for (int j = tileObj->GetInfo()._startIndex.y; j < tileObj->GetInfo()._startIndex.y + count.y; j++)
				{
					//해당 인덱스의 타일의 오브젝트를 지워 준다.
					_vTile[j * _count.x + i]->_tileObj = NULL;
				}
			}

			delete tileObj;

		}
		break;
		case TILEATTRIBUTE::AREA:
		{
			Vector2 count = tileObj->GetInfo()._count;
			Vector2 start = tileObj->GetInfo()._startIndex;

			for (int i = start.x; i < start.x + count.x; i++)
			{
				for (int j = start.y; j < start.y + count.y; j++)
				{
					//해당 인덱스의 타일의 오브젝트를 지워 준다.
					_vTile[j * _count.x + i]->_area = NULL;
				}
			}
			delete tileObj;
		}
		break;
	}
}

Vector2 TileMap::GetWallFrame(Vector2 index, TileAttribute * tileObj)
{
	//주변 네 타일을 검사하고 프레임을 바꿔 줌.
	int wall = 0;

	//상
	if ((index.y - 1) * _count.x + index.x >= 0				&& _vTile[(index.y - 1) * _count.x + index.x]->_wall) wall += 1;
	//하
	if ((index.y + 1) * _count.x + index.x < _tileCount		&& _vTile[(index.y + 1) * _count.x + index.x]->_wall) wall += 2;
	//좌
	if (index.y * _count.x + index.x - 1 >= 0				&& _vTile[index.y * _count.x + index.x - 1]->_wall) wall += 4;
	//우
	if (index.y * _count.x + index.x + 1 < _tileCount		&& _vTile[index.y * _count.x + index.x + 1]->_wall) wall += 8;

	int wallIndex;
	Vector2 realIndex;

	switch (wall)
	{
		case 0:	 wallIndex = 22;	break;		//무
		case 1:	 wallIndex = 14;	break;		//상
		case 2:	 wallIndex = 7;		break;		//하
		case 3:	 wallIndex = 0;		break;		//상하
		case 4:	 wallIndex = 15;	break;		//좌
		case 5:	 wallIndex = 10;	break;		//상좌
		case 6:	 wallIndex = 3;		break;		//하좌
		case 7:	 wallIndex = 19;	break;		//상하좌
		case 8:	 wallIndex = 8;		break;		//우
		case 9:	 wallIndex = 9;		break;		//상우
		case 10: wallIndex = 2;		break;		//하우
		case 11: wallIndex = 18;	break;		//상하우
		case 12: wallIndex = 1;		break;		//좌우
		case 13: wallIndex = 11;	break;		//상좌우
		case 14: wallIndex = 4;		break;		//하좌우
		case 15: wallIndex = 20;	break;		//상하좌우
		default:
		break;
	}
	realIndex.x = wallIndex % 7;
	realIndex.y = wallIndex / 7;
	return realIndex;
}

bool TileMap::CanBuildTile(Vector2 index, TileAttribute * tileObj)
{
	//소지금이 가격보다 적을 경우 만들지 않음.
	if(DATAMANAGER->GetInfo().money < tileObj->GetInfo()._price) return false;

	//범위가 타일맵을 넘어가면 만들지 않음.
	if (index.x >= _count.x - 1 || index.y >= _count.y - 1) return false;

	switch (tileObj->GetInfo()._attribute)
	{
		case TILEATTRIBUTE::TERRAIN:
		{
			//이미 같은 타입의 바닥이 있다면 만들지 못 함.
			if (_vTile[index.y * _count.x + index.x]->_terrain && _vTile[index.y * _count.x + index.x]->_terrain->GetInfo()._type == tileObj->GetInfo()._type) return false;
		}
		break;
		case TILEATTRIBUTE::WALL:
		{
			//이미 오브젝트가 있다면 만들지 못 함.
			if (_vTile[(index.y) * _count.x + index.x]->_tileObj) return false;

			//이미 같은 타입의 벽이 있다면 만들지 못 함.
			 if (_vTile[index.y * _count.x + index.x]->_wall && _vTile[index.y * _count.x + index.x]->_wall->GetInfo()._type == tileObj->GetInfo()._type) return false;
		}
		break;
		case TILEATTRIBUTE::OBJECT:
		{
			//방향이 오른쪽 또는 왼쪽이라면 차지하는 x, y 칸의 개수를 뒤집어 검사 해 준다.
			Vector2 count = tileObj->GetInfo()._count;
			if (tileObj->GetInfo()._direction == DIRECTION::RIGHT || tileObj->GetInfo()._direction == DIRECTION::LEFT)
			{
				count.x = tileObj->GetInfo()._count.y;
				count.y = tileObj->GetInfo()._count.x;
			}

			//이미 벽이나 오브젝트가 있으면 만들지 않음.
			for (int i = index.x; i < index.x + count.x; i++)
			{
				for (int j = index.y; j < index.y + count.y; j++)
				{
					if (_vTile[j * _count.x + i]->_wall || _vTile[j * _count.x + i]->_tileObj) return false;
				}
			}
		}
		break;
		case TILEATTRIBUTE::AREA:
		{
			Vector2 count = tileObj->GetInfo()._count;

			//범위 내에 다른 지역이 있으면 삭제한다.
			if (_vTile[index.y * _count.x + index.x]->_area) DestroyTileObject(_vTile[index.y * _count.x + index.x]->_area);
			
		}

		break;
	}
	return true;
}

TileAttribute * TileMap::FindTileObject(string key)
{
	for (int i = 0; i < _tileCount; i++)
	{
		if (_vTile[i]->_area && _vTile[i]->_area->GetKey() == key)
		{
			return _vTile[i]->_area;
		}

		if (_vTile[i]->_tileObj && _vTile[i]->_tileObj->GetKey() == key)
		{
			return _vTile[i]->_tileObj;
		}
	}
	return nullptr;
}
