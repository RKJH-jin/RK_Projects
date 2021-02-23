#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(float fx, float fy, int iwidth, int iheight)
{
    x = fx;
    y = fy;
    width = maxWidth = iwidth;
    height = maxHeight = iheight;

    _rc = RectMakeCenter(x, y, maxWidth, maxHeight);


    return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
    _rc = RectMakeCenter(x, y - 50, maxWidth, maxHeight);
}

void progressBar::render()
{
 
}

void progressBar::adjRender()
{
    IMAGEMANAGER->render("backBar", getMemDC(), _rc.left, _rc.top,
        0, 0, maxWidth, maxHeight);

    IMAGEMANAGER->adjRender("frontBar", getMemDC(), _rc.left, _rc.top,
        width, maxHeight);
}



void progressBar::setGauge(float currentGauge, float maxGauge)
{
    width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
