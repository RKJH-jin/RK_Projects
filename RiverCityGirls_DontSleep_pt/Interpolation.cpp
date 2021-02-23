#include "stdafx.h"
#include "Interpolation.h"

Interpolation::Interpolation()
{
	_worldTimeCount = 0;
	_isMoving = false;
}

void Interpolation::update()
{
	moving();
}

void Interpolation::moveTo(vector3* pos, float endX, float endY, float time)
{
	if (!_isMoving)
	{
		_pos = pos;
		_startX = _pos->x;	_startY = _pos->y;
		_endX = endX;		_endY = endY;

		_travelRange = getDistance(_startX, _startY, _endX, _endY);
		_angle = getAngle(_startX, _startY, _endX, _endY);

		_worldTimeCount = TIME_M->getWorldTime();
		_time = time;

		_isMoving = true;
	}
}

void Interpolation::moving()
{
	if (!_isMoving) return;

	float elapsedTime = TIME_M->getElapsedTime();
	float moveSpeed = (elapsedTime / _time) * _travelRange;

	_pos->setX(_pos->x + cosf(_angle) * moveSpeed);
	_pos->setY(_pos->y - sinf(_angle) * moveSpeed);

	if (_time + _worldTimeCount <= TIME_M->getWorldTime())
	{
		_worldTimeCount = TIME_M->getWorldTime();

		_pos->setX(_endX);
		_pos->setY(_endY);

		_isMoving = false;
	}
}
