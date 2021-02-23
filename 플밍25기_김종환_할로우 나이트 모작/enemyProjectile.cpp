#include "stdafx.h"
#include "enemyProjectile.h"

HRESULT enemyProjectile::init(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, ENEMY::ENEMYTYPE enemyType, ENEMY::DIRECTIONTYPE dir)
{
    _enemyType = enemyType;
    _dir = dir;
    if (_enemyType == ENEMY::ENEMYTYPE::ASPID)
    {
        aspidProjectileInit(enemyX, enemyY, enemyWidth, enemyHeight, enemyAngle);
    }
    return S_OK;
}

void enemyProjectile::release()
{
}

void enemyProjectile::update()
{
}

void enemyProjectile::render()
{
    
}

void enemyProjectile::aspidProjectileInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle)
{
    _angle = enemyAngle;
   
    _width = 30;
    _height = 30;
    _speed = 10;
    if (_dir == ENEMY::DIRECTIONTYPE::LEFT)
    {
        _x = enemyX - enemyWidth / 2 - _width / 2;
    }
    else
    {
        _x = enemyX + enemyWidth / 2 + _width / 2;
    }
    _y = enemyY + enemyHeight / 2;

    _img = IMAGEMANAGER->findImage("death_core");
    _rc = RectMakeCenter(_x, _y, _width, _height);

    _preX = _x;
    _preY = _y;
}

BOOL enemyProjectile::aspidProjectileMove()
{
    float dis = getDistance(_preX, _preY, _x, _y);
    _x += cosf(_angle) * _speed;
    _y += (-sinf(_angle)) * _speed;
    _rc = RectMakeCenter(_x, _y, _width, _height);
    if (dis < 1000) return false;
    else if (dis >= 1000) return true;
}

void enemyProjectile::aspidProjectileRender()
{
    //Rectangle(getMemDC(), _rc);
    _img->render(getMemDC(), _rc.left - 1, _rc.top - 1);
    
}

void enemyProjectile::xeroProjectileInit(float enemyX, float enemyY, float enemyWidth, float enemyHeight, float enemyAngle, float distance, ENEMY::DIRECTIONTYPE dir)
{
    _angle = 0;
    _width = 42;
    _height = 260;
    _speed = 10;
    _dir = dir;
    
    _enemyType = ENEMY::ENEMYTYPE::XERO;
    if (_dir == ENEMY::DIRECTIONTYPE::LEFT)
    {
        _x = (enemyX - enemyWidth / 2) - distance;
    }
    else
    {
        _x = (enemyX + enemyWidth / 2) + distance;
    }
    _y = enemyY + enemyHeight / 2 - 150;
    _distance = fabs(enemyX - _x);
    _img = IMAGEMANAGER->findImage("xero_spear");
    _rc = RectMakeCenter(_x, _y, _width, _height);

    _preX = _x;
    _preY = _y;
    isFire = false;
    isEnd = false;
}

void enemyProjectile::xeroProjectileMove(float enemyX, float enemyY)
{
    float dist = getDistance(_x, _y, enemyX, enemyY);
    if (_dir == ENEMY::DIRECTIONTYPE::LEFT)
    {
        // enemyX - _distance - 15 < _x < enemyX - _distance + 15
        if (_x < enemyX - _distance - 15)
        {
            _x += _speed;
        }
        else if (_x > enemyX - _distance + 15)
        {
            _x -= _speed;
        }
        
    }
    else if (_dir == ENEMY::DIRECTIONTYPE::RIGHT)
    {
        // enemyX + _distance - 10 < _x < enemyX + _distance + 10
        if (_x  < enemyX + _distance - 15)
        {
            _x += _speed;
        }
        else if (_x  > enemyX + _distance + 15)
        {
            _x -= _speed;
        }
    }
    _rc = RectMakeCenter(_x, _y, _width, _height);
}

void enemyProjectile::xeroProjectileFire(float angle)
{
    _angle = PI / 2 + angle;
    _LT.x = cosf(_angle) * (-_width / 2) + sinf(_angle) * (-_height / 2) + _x;
    _LT.y = -sinf(_angle) * (-_width / 2) + cosf(_angle) * (-_height / 2) + _y;
    _RT.x = cosf(_angle) * (_width / 2) + sinf(_angle) * (-_height / 2) + _x;
    _RT.y = -sinf(_angle) * (-_width / 2) + cosf(_angle) * (-_height / 2) + _y;
    _LB.x = cosf(_angle) * (-_width / 2) + sinf(_angle) * (_height / 2) + _x;
    _LB.y = -sinf(_angle) * (-_width / 2) + cosf(_angle) * (_height / 2) + _y;
    _RB.x = cosf(_angle) * (_width / 2) + sinf(_angle) * (_height / 2) + _x;
    _RB.y = -sinf(_angle) * (-_width / 2) + cosf(_angle) * (_height / 2) + _y;

    pts[0] = _LT;
    pts[1] = _RT;
    pts[2] = _RB;
    pts[3] = _LB;
    
    _preX = _x;
    _preY = _y;
    isFire = true;
}

void enemyProjectile::xeroProjectileFireMove()
{
    _x += cosf(_angle - PI / 2) * _speed * 1.5;
    _y += (-sinf(_angle - PI / 2)) * _speed * 1.5;
    _LT.x = cosf(_angle) * (-_width / 2) + sinf(_angle) * (-_height / 2) + _x;
    _LT.y = -sinf(_angle) * (-_width / 2) + cosf(_angle) * (-_height / 2) + _y;
    _RT.x = cosf(_angle) * (_width / 2) + sinf(_angle) * (-_height / 2) + _x;
    _RT.y = -sinf(_angle) * (_width / 2) + cosf(_angle) * (-_height / 2) + _y;
    _LB.x = cosf(_angle) * (-_width / 2) + sinf(_angle) * (_height / 2) + _x;
    _LB.y = -sinf(_angle) * (-_width / 2) + cosf(_angle) * (_height / 2) + _y;
    _RB.x = cosf(_angle) * (_width / 2) + sinf(_angle) * (_height / 2) + _x;
    _RB.y = -sinf(_angle) * (_width / 2) + cosf(_angle) * (_height / 2) + _y;

    pts[0] = _LT;
    pts[1] = _RT;
    pts[2] = _RB;
    pts[3] = _LB;
}

bool enemyProjectile::xeroProjectileFireMoveCheck(float enemyX, float enemyY, float enemyWidth, float enemyHeight)
{
    float dist = getDistance(_x, _y, _preX, _preY);
    if (dist > 1000)
    {
        if (_dir == ENEMY::DIRECTIONTYPE::LEFT)
        {
            _x = (enemyX - enemyWidth / 2) - _distance;
        }
        else
        {
            _x = (enemyX + enemyWidth / 2) + _distance;
        }
        _y = enemyY + enemyHeight / 2 - 150;
        _rc = RectMakeCenter(_x, _y, _width, _height);
        isEnd = true;
        return true;
    }
    return false;
}

void enemyProjectile::xeroProjectileRender()
{
    Rectangle(getMemDC(), _rc);
    _img->render(getMemDC(), _rc.left, _rc.top);
}

void enemyProjectile::xeroProjectileFireRender()
{
    Polygon(getMemDC(), pts, 4);
    _img->rotateRender(getMemDC(), _x, _y, -_angle);
}
