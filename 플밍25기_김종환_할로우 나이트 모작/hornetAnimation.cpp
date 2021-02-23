#include "stdafx.h"
#include "hornetAnimation.h"

HRESULT hornetAnimation::init(float x, float y)
{
    img = IMAGEMANAGER->findImage("hornet_idle_special_left");

    ANIMATIONMANAGER->addAnimation("hornet_idle_special_left", 
        img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight(), false, true, 1);
    _x = x;
    _y = y;
    
    return S_OK;
}

void hornetAnimation::release()
{
}

void hornetAnimation::update(float x, float y)
{
    _x = x;
    _y = y;
    
    ANIMATIONMANAGER->updateAnimation("hornet_idle_special_left", 10);
}

void hornetAnimation::render()
{
    ANIMATIONMANAGER->aniRender("hornet_idle_special_left", "hornet_idle_special_left", getMemDC(), _x, _y);
    
}
