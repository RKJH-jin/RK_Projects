#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
    render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
        ani->getFrameWidth(), ani->getFrameHeight());
}

void image::alphaAniRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha)
{
    alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
        ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}
