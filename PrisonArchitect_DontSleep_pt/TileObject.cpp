#include "stdafx.h"
#include "TileObject.h"

TileObject::TileObject(TILEOBJECT type)
{
	_info._type = (int)type;
	_info._attribute = TILEATTRIBUTE::OBJECT;
	_type = type;
	_info._direction = DIRECTION::FRONT;

	_frame[0] = 0;		//앞
	_frame[1] = 2;		//왼
	_frame[2] = 1;		//뒤
	_frame[3] = 2;		//오

	_key = DATAMANAGER->_vStr_buf[(int)type * 10 + 0];
	_name = DATAMANAGER->_vStr_buf[(int)type * 10 + 1];
	_description = DATAMANAGER->_vStr_buf[(int)type * 10 + 5];

	_info._count = Vector2(stoi(DATAMANAGER->_vStr_buf[(int)type * 10 + 2]), stoi(DATAMANAGER->_vStr_buf[(int)type * 10 + 3]));
	_info._price = stoi(DATAMANAGER->_vStr_buf[(int)type * 10 + 4]);

	_description = _description + "\n가격은 " + to_string(_info._price) + "원입니다.";

	switch (type)
	{
	case TILEOBJECT::가스레인지:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		break;
	case TILEOBJECT::배식대:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		_vUsable.push_back(Vector2(2, 0));
		break;
	case TILEOBJECT::벤치:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		_vUsable.push_back(Vector2(2, 0));
		_vUsable.push_back(Vector2(3, 0));
		break;
	case TILEOBJECT::변기:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::사무실책상:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::샤워기:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::서류보관함:
		break;
	case TILEOBJECT::쇼파:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		break;
	case TILEOBJECT::식탁:
		_vUsable.push_back(Vector2(0, 0));
		_vUsable.push_back(Vector2(1, 0));
		_vUsable.push_back(Vector2(2, 0));
		break;
	case TILEOBJECT::싱크대:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::의자:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::이중철창문:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::자판기:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::직원문:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::철창문:
		_vUsable.push_back(Vector2(0, 0));
		break;
	case TILEOBJECT::침대:
		_vUsable.push_back(Vector2(0, 0));
		break;
	}

	_info._img = ImageManager::GetInstance()->FindImage(_key);
}

HRESULT TileObject::init()
{
	return E_NOTIMPL;
}

void TileObject::release()
{
}

void TileObject::update()
{
}

void TileObject::render()
{
	//왼쪽 방향이면 가로로 뒤집어 준다.
	if (_info._direction == DIRECTION::LEFT) _info._img->SetReverseX(true);

	_info._img->FrameRender(_info._renderPos, _frame[(int)_info._direction], 0, CAMERAMANAGER->GetMainCamera());
}

void TileObject::Build(Vector2 index)
{
	TileAttribute::Build(index);


	_info._renderPos = Vector2(_info._pos.x + (GetCount().x*TILESIZE) / 2,
		_info._pos.y + (GetCount().y*TILESIZE) - _info._img->GetFrameSize().y / 2);

	if (_info._direction == DIRECTION::FRONT || _info._direction == DIRECTION::BACK)
	{

	}
	else if (_info._direction == DIRECTION::RIGHT || _info._direction == DIRECTION::LEFT)
	{
		//옆모습이라면 뒤집는다.
		for (int i = 0; i < _vUsable.size(); i++)
		{
			_vUsable[i].Swap();
			_vUsable[i].Swap();
		}
	}

	for (int i = 0; i < _vUsable.size(); i++)
	{
		_vUsable[i].x += index.x;
		_vUsable[i].y += index.y;
	}
}

void TileObject::Destroy()
{
}

bool TileObject::CheckVoidIndex()
{
    if (!_vUsable.empty()) return true;
    return false;
}

Vector2* TileObject::GetVoidIndexfromVector()
{
	//벡터가 비어 있으면 null을 반환한다.
	if (_vUsable.empty()) return nullptr;

	//벡터가 비어있지 않다면 인덱스를 리턴한다.
	Vector2* index = &_vUsable[0];
	_vUsable.erase(_vUsable.begin());
	return index;
}

void TileObject::PutIndexToVector(Vector2* index)
{
	_vUsable.push_back(*index);
}
BOOST_CLASS_EXPORT(TileObject)