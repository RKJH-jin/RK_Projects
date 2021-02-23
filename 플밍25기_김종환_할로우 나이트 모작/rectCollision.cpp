#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "projectile.h"

tagCollisionCheck player::rectCollision()
{
    tagCollisionCheck tagTemp;
    tagTemp.boolValue = false;

    for (int i = 0; i < _cMapManager->getVObject().size(); ++i)
    {
        RECT temp;
        if (IntersectRect(&temp, &_player.rc, &_cMapManager->getVObject()[i]->getRect()))
        {
            tagTemp.boolValue = true;
            tagTemp.objectRect = _cMapManager->getVObject()[i]->getRect();
            break;
        }
    }

    return tagTemp;
}