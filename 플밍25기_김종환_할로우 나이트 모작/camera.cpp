#include "stdafx.h"
#include "camera.h"

camera::camera()
    :_cameraInfo(NULL)
{
}

camera::~camera()
{
}

HRESULT camera::init(float x, float y, int width, int height, int mag)
{
    _cameraInfo = new CAMERA_INFO;
    _cameraInfo->centerX = x;
    _cameraInfo->centerY = y;
    _cameraInfo->cameraWidth = width;
    _cameraInfo->cameraHeight = height;
    _cameraInfo->cameraLT.x = _cameraInfo->centerX - _cameraInfo->cameraWidth / 2;
    _cameraInfo->cameraLT.y = _cameraInfo->centerY - _cameraInfo->cameraHeight / 2;
    _cameraInfo->cameraRB.x = _cameraInfo->centerX + _cameraInfo->cameraWidth / 2;
    _cameraInfo->cameraRB.y = _cameraInfo->centerY + _cameraInfo->cameraHeight / 2;

    _cameraInfo->Magnification = mag;

    return S_OK;
}



void camera::release()
{
    SAFE_DELETE(_cameraInfo);
}

void camera::updateVertax()
{
    _cameraInfo->cameraLT.x = _cameraInfo->centerX - _cameraInfo->cameraWidth / 2;
    _cameraInfo->cameraLT.y = _cameraInfo->centerY - _cameraInfo->cameraHeight / 2;
    _cameraInfo->cameraRB.x = _cameraInfo->centerX + _cameraInfo->cameraWidth / 2;
    _cameraInfo->cameraRB.y = _cameraInfo->centerY + _cameraInfo->cameraHeight / 2;
}





