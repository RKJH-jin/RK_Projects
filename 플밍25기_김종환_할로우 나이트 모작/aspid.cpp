#include "stdafx.h"
#include "aspid.h"



HRESULT aspid::init(float x, float y)
{
    enemy::aspidInit(x, y);

    return S_OK;
}

void aspid::release()
{
    enemy::release();
}

void aspid::update()
{
    enemy::update();
}

void aspid::render()
{
    enemy::render();
}






