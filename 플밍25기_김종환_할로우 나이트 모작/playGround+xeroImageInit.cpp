#include "stdafx.h"
#include "playGround.h"

void playGround::xeroImageInit()
{
    IMAGEMANAGER->addFrameImage("xero_idle", "image/enemy/xero/xero_idle.bmp", 1224, 336, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("xero_attack", "image/enemy/xero/xero_attack.bmp", 2292, 317, 6, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addImage("xero_spear", "image/enemy/xero/xero_spear_down.bmp", 42, 260, true, RGB(255, 0, 255));
}