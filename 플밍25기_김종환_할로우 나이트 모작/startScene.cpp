#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
    IMAGEMANAGER->addImage("우주", "image/우주.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
    _mainCamera = CAMERAMANAGER->getMainCamera();
    x = WINSIZEX / 2;
    y = WINSIZEY / 2;
    return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        x -= 5;
    }

    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        x += 5;
    }
    //===========================카메라 위치 업데이트(필수)============================//
    CAMERAMANAGER->mainCameraUpdate(x, y);			// 메인카메라 위치 업데이트! 필수!! (centerX, centerY)
}

void startScene::render()
{
    IMAGEMANAGER->findImage("우주")->render(getMemDC());
}
