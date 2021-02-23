#include "stdafx.h"
#include "TransformC.h"

void TransformC::SetPosition(Vector2 pos)
{
	_pos = pos;

	if (!_object->GetvChild().empty())
	{
		for (int i = 0; i < _object->GetvChild().size(); i++)
		{
			_object->GetvChild()[i]->GetTransform()->SetPosition(_object->GetvChild()[i]->GetTransform()->GetPivot() + _pos);
		}
	}

	_index.x = (int)_pos.x / TILESIZE;
	_index.y = (int)_pos.y / TILESIZE;
}

RECT TransformC::GetRect()
{
	RECT result;
	if (_camera) result = RectMakeCenter(_camera->GetRelativePos(_pos).x, _camera->GetRelativePos(_pos).y,
		_size.x*_camera->_zoom, _size.y*_camera->_zoom);
	else result = RectMakeCenter(_pos.x, _pos.y, _size.x, _size.y);

	return result;
}

void TransformC::Translate(Vector2 delta)
{
	//자식 이동
	for (GameObject* c : _object->GetvChild())
		c->GetTransform()->Translate(delta);

	//본인 이동
	SetPosition(_pos + delta);

	if (delta.x < 0)	SetDirection(DIRECTION::LEFT);
	if (delta.x > 0)	SetDirection(DIRECTION::RIGHT);
	if (delta.y < 0)	SetDirection(DIRECTION::BACK);
	if (delta.y > 0)	SetDirection(DIRECTION::FRONT);

}

void TransformC::SetRect()
{
	if (_camera)
	{
		_rc = RectMakePivot(_camera->GetRelativePos(_pos), _size*_camera->_zoom, Pivot::Center);
	}

	else
	{
		_rc = RectMakePivot(_pos, _size, Pivot::Center);
	}
}


void TransformC::Init()
{

}

void TransformC::Update()
{
	SetRect();

}

void TransformC::Render()
{
	
}

