#include "stdafx.h"
#include "platform.h"

HRESULT platform::init(float x, float y, int width, int height, objectType type)
{
    object::init(x, y, width, height, type);
    return S_OK;
}

void platform::release()
{
    object::release();
}

void platform::update()
{
    object::update();
}

void platform::render()
{
    object::render();
}
