#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

BOOL player::pixelCheckLeft()
{
    for (int j = _player.y - _player.height / 2; j < _player.y + _player.height / 2; ++j)
    {
        for (int i = _player.x - _player.width / 2 + 10; i >= _player.x - _player.width / 2 - 10; --i)
        {
            COLORREF color = GetPixel(getPixelMemDC(), i, j);
            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);
            if (r == 255 && g == 0 && b == 254)
            {
                _player.x = i + _player.width / 2;
                return true;
            }
        }
    }
    return false;
}

BOOL player::pixelCheckRight()
{
    for (int j = _player.y - _player.height / 2; j < _player.y + _player.height / 2; ++j)
    {
        for (int i = _player.x + _player.width / 2 - 10; i <= _player.x + _player.width / 2 + 10; ++i)
        {
            COLORREF color = GetPixel(getPixelMemDC(), i, j);
            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);
            if (r == 255 && g == 0 && b == 254)
            {
                _player.x = i - _player.width / 2;
                return true;
            }
        }
    }
    return false;
}


BOOL player::pixelCheckUp()
{
    for (int i = _player.x - _player.width / 2; i <= _player.x + _player.width / 2; ++i)
    {
        for (int j = _player.y - _player.height / 2 - 4; j <= _player.y - _player.height / 2 + 10; ++j)
        {
            COLORREF color = GetPixel(getPixelMemDC(), i, j);
            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);
            if (r == 255 && g == 0 && b == 252)
            {
                _player.y = j + _player.height / 2;
                return true;
            }
        }
    }
    return false;
}

BOOL player::pixelCheckDown()
{
    
    for (int i = _player.x - _player.width / 2 + 9; i <= _player.x + _player.width / 2 - 9; ++i)
    {
        for (int j = _player.y + _player.height / 2 - 10; j <= _player.y + _player.height / 2 + 4; ++j)
        {
           
            COLORREF color = GetPixel(getPixelMemDC(), i, j);
            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);
            
            if (r == 255 && g == 0 && b == 253)
            {
                _player.y = j - _player.height / 2;
               
                return true;
            }
        }
    }
    return false;
}

BOOL player::pixelCheckDownLeft()
{
    for (int i = _player.x - _player.width / 2 - 30; i <= _player.x - _player.width / 2 + 5; ++i)
    {
        for (int j = _player.y + _player.height / 2 - 10; j <= _player.y + _player.height / 2 + 4; ++j)
        {
            int tempNum = j - _player.rc.bottom;
            COLORREF color = GetPixel(getPixelMemDC(), i, j);
            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);
            if (r == 255 && g == 0 && b == 253)
            {
                _player.y = j - _player.height / 2;         
                return true;
            }
        }
    }
    return false;
}

BOOL player::pixelCheckDownRight()
{
    for (int i = _player.x + _player.width / 2 + 5; i <= _player.x + _player.width / 2 + 30; ++i)
    {
        for (int j = _player.y + _player.height / 2 - 10; j <= _player.y + _player.height / 2 + 4; ++j)
        {
            int tempNum = j - _player.rc.bottom;
            COLORREF color = GetPixel(getPixelMemDC(), i, j);
            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);
            if (r == 255 && g == 0 && b == 253)
            {
                _player.y = j - _player.height / 2;
                return true;
            }
        }
    }
    return false;
}
