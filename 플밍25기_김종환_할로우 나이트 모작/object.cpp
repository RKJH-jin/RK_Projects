#include "stdafx.h"
#include "object.h"

HRESULT object::init(float x, float y, int width, int height, objectType type)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _type = type;
    _rc = RectMakeCenter(_x, _y, _width, _height);
    //=============이미지 추가==============//
    _img = new image;

    //오른쪽 벽면
    for (int i = x + width / 2 - 4; i < x + width / 2; ++i)
    {
        for (int j = y - height / 2 + 5; j <= y + height / 2 - 5; ++j)
        {
            SetPixel(getPixelMemDC(), i, j, RGB(255, 0, 254));
        }
    }

    //왼쪽 벽면
    for (int i = x - width / 2 + 1; i <= x - width / 2 + 4; ++i)
    {
        for (int j = y - height / 2 + 5; j <= y + height / 2 - 5; ++j)
        {
            SetPixel(getPixelMemDC(), i, j, RGB(255, 0, 254));
        }
    }
    
    //위쪽 벽면
    for (int i = x - width / 2; i <= x + width / 2; ++i)
    {
        for (int j = y - height / 2; j <= y - height / 2 + 10; ++j)
        {
            SetPixel(getPixelMemDC(), i, j, RGB(255, 0, 253));
        }
    }

    //아래쪽 벽면
    for (int i = x - width / 2; i <= x + width / 2; ++i)
    {
        for (int j = y + height / 2 - 10; j <= y + height / 2; ++j)
        {
            SetPixel(getPixelMemDC(), i, j, RGB(255, 0, 252));
        }
    }
    return S_OK;
}

void object::release()
{
}

void object::update()
{
}

void object::render()
{
    Rectangle(getMemDC(), _rc);
}
