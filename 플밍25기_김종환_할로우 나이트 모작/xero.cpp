#include "stdafx.h"
#include "xero.h"

HRESULT xero::init(float x, float y)
{
    enemy::xeroInit(x, y);
    return S_OK;
}

void xero::release()
{
    enemy::release();
}

void xero::update()
{
    enemy::update();
}

void xero::render()
{
    enemy::render();
}
