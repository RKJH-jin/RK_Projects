#include "stdafx.h"
#include "pixelCollision.h"

HRESULT pixelCollision::init()
{
    IMAGEMANAGER->addImage("hill", "image/mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

    _ball = IMAGEMANAGER->addImage("ball", "image/ball.bmp", 60, 60, true, RGB(255, 0, 255));

    _x = WINSIZEX / 2 - 100;
    _y = WINSIZEY / 2 + 100;

    _rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
    _probeY = _y + _ball->getHeight() / 2;
    
    return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::update()
{
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _x -= 3.0f;
    }

    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _x += 3.0f;
    }

    _probeY = _y + _ball->getHeight() / 2;

    for (int i = _probeY - 50; i < _probeY + 50; ++i)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("hill")->getMemDC(), _x, i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            _y = i - _ball->getHeight() / 2;
            break;
        }
    }

    _rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

}

void pixelCollision::render()
{

    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
    {
        HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
        HBRUSH oldBrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("hill")->getMemDC(), brush);

        HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
        HPEN oldPen = (HPEN)SelectObject(IMAGEMANAGER->findImage("hill")->getMemDC(), pen);

        EllipseMakeCenter(IMAGEMANAGER->findImage("hill")->getMemDC(), _ptMouse.x, _ptMouse.y, 60, 60);

        brush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage("hill")->getMemDC(), oldBrush);
        DeleteObject(brush);
        pen = (HPEN)SelectObject(IMAGEMANAGER->findImage("hill")->getMemDC(), pen);
        DeleteObject(pen);
    }


    IMAGEMANAGER->findImage("hill")->render(getMemDC());
    _ball->render(getMemDC(), _rc.left, _rc.top);
}
