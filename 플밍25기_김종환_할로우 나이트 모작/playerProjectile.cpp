#include "stdafx.h"
#include "playerProjectile.h"

HRESULT playerProjectile::init(float playerX, float playerY, float playerWidth, float playerHeight, PLAYER::DIRECTION dir)
{
    _dir = dir;
    _width = 230;
    _height = 25;
    if (_dir == PLAYER::DIRECTION::LEFT)
    {
        _img = IMAGEMANAGER->findImage("hornet_spear_left");
        _x = playerX - playerWidth / 2 - _width / 2;
        _y = playerY;
    }
    else
    {
        _img = IMAGEMANAGER->findImage("hornet_spear_right");
        _x = playerX + playerWidth / 2 + _width / 2;
        _y = playerY;
    }
    _preX = _x;
    _preY = _y;
    _rc = RectMakeCenter(_x, _y, _width, _height);
    _speed = 20;
    isStart = false;
    isEnd = false;
    return S_OK;
}

void playerProjectile::release()
{
}

void playerProjectile::update()
{
    hornetSpearMove();
}

void playerProjectile::render()
{
    //Rectangle(getMemDC(), _rc);
    _img->render(getMemDC(), _rc.left, _rc.top);
}


// 창이 날라가는 중이면 false, 다 날라갔으면 false를 내뱉음으로 하면 안되네 ㅅㅂ...
void playerProjectile::hornetSpearMove()
{
    if (_dir == PLAYER::DIRECTION::LEFT)
    {
        _x -= _speed;
        if (fabs(_preX - _x) > 500)
        {
            _speed *= (-1);
            _x -= _speed;
            isStart = true;
        }
        if (_x >= _preX && isStart) isEnd = true;
    }
    else
    {
        _x += _speed;
        if (fabs(_preX - _x) > 500)
        {
            _speed *= (-1);
            _x += _speed;
            isStart = true;
        }
        if (_x <= _preX && isStart) isEnd = true;
    }

    _rc = RectMakeCenter(_x, _y, _width, _height);
}

BOOL playerProjectile::hornetSpearCheck()
{
    if (isEnd) return true;
    else return false;
}
