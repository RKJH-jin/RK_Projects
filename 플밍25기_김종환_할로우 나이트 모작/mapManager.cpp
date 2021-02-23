#include "stdafx.h"
#include "mapManager.h"
#include "player.h"

mapManager::mapManager()
    :_gravity(0.98f)
{
}

mapManager::~mapManager()
{
}

HRESULT mapManager::init()
{
    _townFloor1 = new platform;
    _townFloor1->init(3600, WINSIZEY - 100, 7225, 96, GROUND);
    _townFloor1->setImage(IMAGEMANAGER->findImage("town_floor_1"));
    _vTownObject.push_back(_townFloor1);
    
    _townWallLeft = new platform;
    _townWallLeft->init(50, WINSIZEY / 2, 750, 1080, WALL);
    _townWallLeft->setImage(IMAGEMANAGER->findImage("town_wall_left"));
    _vTownObject.push_back(_townWallLeft);

    platformInit(WINSIZEX / 2, WINSIZEY / 2 + 200, 170, 75, "floor_1", PLATFORM);
    platformInit(WINSIZEX / 2 + 500, WINSIZEY / 2 + 200, 170, 75, "floor_1", PLATFORM);
    platformInit(WINSIZEX / 2 + 1000, WINSIZEY / 2 + 200, 170, 75, "floor_1", PLATFORM);
    platformInit(WINSIZEX / 2 + 1500, WINSIZEY / 2 + 200, 170, 75, "floor_1", PLATFORM);

    platformInit(4000, WINSIZEY / 2 + 200, 313, 386, "basketwall_1", PLATFORM);
    platformInit(5000, WINSIZEY / 2, 1195, 249, "floor_2", PLATFORM);
    platformInit(7000, WINSIZEY / 2, 313, 1080, "basketwall_3", WALL);
    return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
{
}

void mapManager::render()
{

    for (int i = 0; i < _vTownObject.size(); ++i)
    {
        
        _vTownObject[i]->getImage()->render(getMemDC(), _vTownObject[i]->getRect().left, _vTownObject[i]->getRect().top);
    }
    _townFloor1->getImage()->render(getMemDC(), _townFloor1->getRect().left, _townFloor1->getRect().top - 5);
    _townWallLeft->getImage()->render(getMemDC(), _townWallLeft->getRect().left, _townWallLeft->getRect().top);
    _platform1->getImage()->render(getMemDC(), _platform1->getRect().left, _platform1->getRect().top - 10);
    IMAGEMANAGER->findImage("town_wall_left_3")->render(getMemDC(), _townWallLeft->getRect().right, _townFloor1->getRect().top - 220);
}

void mapManager::platformInit(float x, float y, float width, float height, string imgKey, objectType obj)
{
    _platform1 = new platform;
    _platform1->init(x, y, width, height, obj);
    _platform1->setImage(IMAGEMANAGER->findImage(imgKey));
    _vTownObject.push_back(_platform1);
}
